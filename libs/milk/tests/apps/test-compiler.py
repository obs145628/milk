import os
import sys

TOP_TESTS_DIR = os.path.join(os.path.dirname(os.path.realpath(__file__)),
                             "../../../../tests")
sys.path.append(TOP_TESTS_DIR)

from pyobts.testsuite import TestSuite
from pyobts.testfinder import FilesTestFinder
from pyobts.cmdrunner import CmdRunner, CmdTest, checker_str, checker_empty, checker_file
import pyobts.cmdrunner as cmdr

STAGES = {
    'parse': 3,
}

ERR_CODES = {
    'lex': 2,
    'parse': 3
}

BUILD_DIR = sys.argv[1]
PY_DIR = os.path.dirname(os.path.realpath(__file__))
MODE = os.getenv('MILK_CL_TEST', 'parse')

TMP_DIR = '/tmp/tests_milk_cl'
SAMPLES_DIR = os.path.join(PY_DIR, '../samples')
CC_PATH = '/usr/bin/gcc'
MKCL_PATH = os.path.join(BUILD_DIR, 'bin/mkcl')


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
        #elif os.path.isfile(self.c_path):
        #    return 'run'
        else:
            return 'parse'

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
        check_err = checker_empty() if exp_ret == 0 else None
        return CmdTest(LEXER_PATH, [self.path], exp_ret=exp_ret, check_err=check_err)

    def cmd_mkcl(self, exp_ret, others=None):
        src = [self.path]
        if others is None:
            others = []
            
        others += ['--custom-ret-code']
        check_err = checker_empty() if exp_ret == 0 else None
        return CmdTest(MKCL_PATH, src + others, exp_ret=exp_ret, check_err=check_err)

    def cmd_cc(self, src_file, out_bin):
        args = [src_file, '-o', out_bin]
        return CmdTest(CC_PATH, args, exp_ret=0, check_out=checker_empty(), check_err=checker_empty())

    def cmd_bin_save(self, bin_path, out_file):
        return CmdTest(bin_path, [], exp_ret=0, out_save_path=out_file)

    def cmd_bin_check(self, bin_path, out_file):
        return CmdTest(bin_path, [], exp_ret=0, check_out=checker_file(out_file))
    
    def get_cmds(self):
        stage, valid = self.get_test_type()
        ret_code = 0 if valid else ERR_CODES[stage]

        if stage == 'parse':
            return [self.cmd_mkcl(exp_ret=ret_code, others=['--stage-parse'])]

        else:
            return None
            

    @staticmethod
    def get_runner():
        def runner_fn(path):
            builder = TestBuilder(path)
            return builder.get_cmds()

        return CmdRunner(runner_fn)
    

if __name__ == '__main__':
    os.makedirs(TMP_DIR, exist_ok=True)
    
    finder = FilesTestFinder()
    finder.add_dir(os.path.join(SAMPLES_DIR, 'grammar'), False)
    finder.add_dir(os.path.join(SAMPLES_DIR, 'algos'), False)
    finder.add_filter_endswith('.mk')
    tests = finder.find()
    
    runner = TestBuilder.get_runner()
    ts = TestSuite('Milk Compiler', tests, runner)
    ts.run_and_exit()
