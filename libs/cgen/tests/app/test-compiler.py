import os
import sys

TOP_TESTS_DIR = os.path.join(os.path.dirname(os.path.realpath(__file__)),
                             "../../../../tests")
sys.path.append(TOP_TESTS_DIR)

from pyobts.basicts import Result
from cgents import CgenTS
import pyobts.ucmd as ucmd

ERR_MSG = '''Invalid return code: expected {}, got {}
(output)
<BEG>{}<END>
(err):
<BEG>{}<END>'''

PREPARE_ERR_MSG = '''Prepare command '{}' failed with code {}:
(output)
<BEG>{}<END>
(err):
<BEG>{}<END>'''

INVALID_OUTPUT_ERR_MSG = '''Invalid output:
(you)
<BEG>{}<END>
(ref):
<BEG>{}<END>'''

MODE = os.getenv('CGEN_CC_TEST', 'run')
TMP_DIR = '/tmp/tests_cgen_cc'
CC_PATH = '/usr/bin/gcc'

class CgenCCTS(CgenTS):

    def __init__(self):
        super().__init__('cgen lexer')
        self.lexer_bin = os.path.join(self.build_dir, "bin/cgen-test-lexer")
        self.cc_bin = os.path.join(self.build_dir, "bin/cgen-cc")
        self.std_src = os.path.join(self.samples_dir, "../../cgen-libs/cgen-std/lib.cg")
        self.std_lib = os.path.join(self.build_dir, "./lib/libcgen-libs-std.a")
        os.makedirs(TMP_DIR, exist_ok=True)

    def get_test_type(self):

        if MODE == 'lexer' or self.t_err == 'lex':
            exp_code = 1 if self.t_err == 'lex' else 0
            return 'lexer', exp_code

        elif MODE == 'parser' or self.t_err == 'parse':
             exp_code = 1 if self.t_err == 'parse' else 0
             return 'parser', exp_code

        elif MODE == 'type' or self.t_err == 'type':
            exp_code = 1 if self.t_err == 'type' else 0
            return 'type', exp_code

        elif MODE == 'compile':
            exp_code = 0
            return 'compile', exp_code

        elif MODE == 'run':
            exp_code = 0
            cref = os.path.join(self.samples_dir, '{}.c'.format(self.t_name))
            if not os.path.isfile(cref):
                return 'compile', exp_code
            return 'run', exp_code
        
        else:
            print('Internal testsuite error: unknown mode {}'.format(MODE))
            sys.exit(1)


    def run_prepare_cmd(self, cmd):        
        ret, out, err = ucmd.run_cmd(cmd)
        out = out.decode('ascii', 'ignore')
        err = err.decode('ascii', 'ignore')
        if ret == 0:
            return Result.Ok(), out, err

        msg = PREPARE_ERR_MSG.format(' '.join(cmd), ret,
                                     out, err)
        return Result.Err(msg), out, err

    def prehook_buildref(self):
        cref = os.path.join(self.samples_dir, '{}.c'.format(self.t_name))
        outref = os.path.join(self.samples_dir, '{}.out'.format(self.t_name))
        bin_ref = os.path.join(TMP_DIR, 'bin_ref_{}.out'.format(self.t_name))
        if os.path.isfile(outref):
            return Result.Ok()

        res, _1, _2 = self.run_prepare_cmd([CC_PATH, cref, '-o', bin_ref])
        if not res.ok:
            return res

        res, ref_out, _ = self.run_prepare_cmd([bin_ref])
        if not res.ok:
            return res

        with open(outref, 'w') as f:
            f.write(ref_out)
        return Result.Ok()

    def posthook_check_output(self):
        ref_file = os.path.join(self.samples_dir, '{}.out'.format(self.t_name))
        out_bin = os.path.join(TMP_DIR, '{}.out'.format(self.t_name))

        ref_str = None
        with open(ref_file, 'r') as f:
            ref_str = str(f.read())

        res, out_str, _ = self.run_prepare_cmd([out_bin])
        if not res.ok:
            return res

        if ref_str != out_str:
            msg = INVALID_OUTPUT_ERR_MSG.format(out_str, ref_str)
            return Result.Err(msg)

        return Result.Ok()
        
    def run(self, t):
        self.get_test_details(t)
        ttype, exp_code = self.get_test_type()
        src = [self.t_path_cg]
        prehooks = []
        posthooks = []
        
        if ttype == 'lexer':
            cmd = [self.lexer_bin]

        elif ttype == 'parser':
            cmd = [self.cc_bin]
            cmd += ['--stage-parse']

        elif ttype == 'type':
            cmd = [self.cc_bin]
            cmd += ['--stage-type']
            src += [self.std_src]

        elif ttype == 'compile':
            
            out_obj = os.path.join(TMP_DIR, '{}.o'.format(self.t_name))
            cmd = [self.cc_bin]
            cmd += ['--build-object', '--output', out_obj]
            src += [self.std_src]

        elif ttype == 'run':
            prehooks.append(self.prehook_buildref)
            posthooks.append(self.posthook_check_output)
            out_bin = os.path.join(TMP_DIR, '{}.out'.format(self.t_name))
            cmd = [self.cc_bin]
            cmd += ['--build-binary', '--output', out_bin]
            src += [self.std_src]
            cmd += ['--cc-libs', self.std_lib]

            
        cmd += src
        
        for hook in prehooks:
            res = hook()
            if not res.ok:
                return res
        

        ret, out, err = ucmd.run_cmd(cmd)
        valid = ret == exp_code
        if not valid:
            msg = ERR_MSG.format(exp_code, ret,
                                 out.decode('ascii', 'ignore'),
                                 err.decode('ascii', 'ignore'))  
            return Result.Err(msg)

        for hook in posthooks:
            res = hook()
            if not res.ok:
                return res

        return Result.Ok()

if __name__ == '__main__':
    ts = CgenCCTS()
    valid = ts.run_all()
    sys.exit(0 if valid else 1)
