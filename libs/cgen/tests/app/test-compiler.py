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

MODE = os.getenv('CGEN_CC_TEST', 'type')

class CgenLexerTS(CgenTS):

    def __init__(self):
        super().__init__('cgen lexer')
        self.lexer_bin = os.path.join(self.build_dir, "bin/cgen-test-lexer")
        self.cc_bin = os.path.join(self.build_dir, "bin/cgen-cc")
        self.std_src = os.path.join(self.samples_dir, "../../cgen-libs/cgen-std/lib.cg")

    def run(self, t):
        self.get_test_details(t)
        src = [self.t_path_cg]

        if MODE == 'lexer' or self.t_err == 'lex':
            if self.t_err == 'lex':
                exp_code = 1
            else:
                exp_code = 0
            cmd = [self.lexer_bin]

        elif MODE == 'parser' or self.t_err == 'parse':
            if self.t_err == 'parse':
                exp_code = 1
            else:
                exp_code = 0
            cmd = [self.cc_bin]
            cmd += ['--stage-parse']

        elif MODE == 'type' or self.t_err == 'type':
            if self.t_err == 'type':
                exp_code = 1
            else:
                exp_code = 0
            cmd = [self.cc_bin]
            cmd += ['--stage-type']
            src += [self.std_src]
 
        else:
            print('Internal testsuite error: unknown mode {}'.format(MODE))
            sys.exit(1)
        

        cmd += src
        ret, out, err = ucmd.run_cmd(cmd)
        valid = ret == exp_code
        if valid:
            return Result.Ok()
        else:
            msg = ERR_MSG.format(exp_code, ret,
                                 out.decode('ascii', 'ignore'),
                                 err.decode('ascii', 'ignore'))  
            return Result.Err(msg)

if __name__ == '__main__':
    ts = CgenLexerTS()
    valid = ts.run_all()
    sys.exit(0 if valid else 1)
