import os
import sys

TOP_TESTS_DIR = os.path.join(os.path.dirname(os.path.realpath(__file__)),
                             "../../../../tests")
sys.path.append(TOP_TESTS_DIR)

from pyobts.testsuite import TestSuite
from pyobts.testfinder import FilesTestFinder
import pyobts.cmdrunner as cmdr

STAGES = {
    'lex': 2,
    'parse': 3,
    'type': 4,
    'compile': 5,
    'run': 11
}

ERR_CODES = {
    'lex': 2,
    'parse': 3,
    'type': 4,
}

BUILD_DIR = sys.argv[1]
PY_DIR = os.path.dirname(os.path.realpath(__file__))
MODE = os.getenv('CGEN_CC_TEST', 'run')

TMP_DIR = '/tmp/tests_cgen_cc'
SAMPLES_DIR = os.path.join(PY_DIR, '../examples')
CC_PATH = '/usr/bin/gcc'
LEXER_PATH = os.path.join(BUILD_DIR, 'bin/cgen-test-lexer')
CGEN_CL_PATH = os.path.join(BUILD_DIR, 'bin/cgen-cc')
STD_SRC_PATH = os.path.join(SAMPLES_DIR, '../../cgen-libs/cgen-std/lib.cg')
STD_LIB_PATH = os.path.join(BUILD_DIR, './lib/libcgen-libs-std.a')


class TestBuilder:

    UNIQUE_COUNT = 0
    
    def __init__(self, path):
        self.path = path
        self.dir_path = os.path.dirname(self.path)
        self.name = os.path.splitext(os.path.basename(self.path))[0]
        self.stage_err = None
        if self.name.startswith('err_'):
            self.stage_err = self.name.split('_')[1]
        self.c_path = os.path.join(self.dir_path, '{}.c'.format(self.name))
        self.out_path = os.path.join(self.dir_path, '{}.out'.format(self.name))
        

    # gives a unique identifier, based on file name
    def unique(self):
        TestBuilder.UNIQUE_COUNT += 1
        return '{}_{}'.format(self.name, TestBuilder.UNIQUE_COUNT)
        
    
    # Returns the actual stage the file can be run (MODE ignored)
    def get_file_stage(self):
        if self.stage_err is not None:
            return self.stage_err
        elif os.path.isfile(self.c_path):
            return 'run'
        else:
            return 'compile'

    # Returns the stage the file is run (using MODE), and if the test succeeds
    def get_test_type(self):

        fstage = self.get_file_stage()
        fcode = STAGES[fstage]
        mcode = STAGES[MODE]

        real_code = min(fcode, mcode)
        err_code = 999 if self.stage_err is None else STAGES[self.stage_err]

        valid = real_code < err_code
        stage = fstage if real_code == fcode else MODE
        return stage, valid

    def cmd_lexer(self, exp_ret):
        check_err = cmdr.checker_empty() if exp_ret == 0 else None
        return cmdr.CmdTest(LEXER_PATH, [self.path], exp_ret=exp_ret, check_err=check_err)

    def cmd_cgen_cl(self, exp_ret, others=None, use_std=False, out_obj=None, out_bin=None):
        assert (not (out_obj is not None and out_bin is not None))
        src = [self.path]
        if others is None:
            others = []
        if use_std:
            src += [STD_SRC_PATH]
            others += ['--cc-libs', STD_LIB_PATH]

        if out_obj is not None:
            others += ['--build-object', '--output', out_obj]
        if out_bin is not None:
            others += ['--build-binary', '--output', out_bin]
            
            
        others += ['--custom-ret-code']
        check_err = cmdr.checker_empty() if exp_ret == 0 else None
        return cmdr.CmdTest(CGEN_CL_PATH, src + others, exp_ret=exp_ret, check_err=check_err)

    def cmd_cc(self, src_file, out_bin):
        args = [src_file, '-o', out_bin]
        return cmdr.CmdTest(CC_PATH, args, exp_ret=0, check_out=cmdr.checker_empty(), check_err=cmdr.checker_empty())

    def cmd_bin_save(self, bin_path, out_file):
        return cmdr.CmdTest(bin_path, [], exp_ret=0, out_save_path=out_file)

    def cmd_bin_check(self, bin_path, out_file):
        return cmdr.CmdTest(bin_path, [], exp_ret=0, check_out=cmdr.checker_file(out_file))
    
    def get_cmds(self):
        stage, valid = self.get_test_type()
        ret_code = 0 if valid else ERR_CODES[stage]

        if stage == 'lex':
            return [self.cmd_lexer(exp_ret=ret_code)]

        elif stage == 'parse':
            return [self.cmd_cgen_cl(exp_ret=ret_code, others=['--stage-parse'])]

        elif stage == 'type':
            return [self.cmd_cgen_cl(exp_ret=ret_code, others=['--stage-type'], use_std=True)]

        elif stage == 'compile':
            out_obj = os.path.join(TMP_DIR, '{}.o'.format(self.unique()))
            return [self.cmd_cgen_cl(exp_ret=ret_code, use_std=True, out_obj=out_obj)]
        
        elif stage == 'run':
            cmds = []
            out_bin = os.path.join(TMP_DIR, '{}.bin'.format(self.unique()))

            if not os.path.isfile(self.out_path):
                ref_bin = os.path.join(TMP_DIR, '{}_ref.bin'.format(self.unique()))
                cmds += [self.cmd_cc(self.c_path, ref_bin)]
                cmds += [self.cmd_bin_save(ref_bin, self.out_path)]

            cmds += [self.cmd_cgen_cl(exp_ret=ret_code, use_std=True, out_bin=out_bin)]
            cmds += [self.cmd_bin_check(out_bin, self.out_path)]
            return cmds

        else:
            return None


    @staticmethod
    def get_runner():
        def runner_fn(path):
            builder = TestBuilder(path)
            return builder.get_cmds()

        return cmdr.CmdRunner(runner_fn)
    

if __name__ == '__main__':
    os.makedirs(TMP_DIR, exist_ok=True)
    
    finder = FilesTestFinder()
    finder.add_dir(SAMPLES_DIR, False)
    finder.add_filter_endswith('.cg')
    tests = finder.find()
    
    runner = TestBuilder.get_runner()
    ts = TestSuite('Cgen Compiler', tests, runner)
    ts.run_and_exit()
