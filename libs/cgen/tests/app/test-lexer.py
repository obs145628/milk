import os
import sys

TOP_TESTS_DIR = os.path.join(os.path.dirname(os.path.realpath(__file__)),
                             "../../../../tests")
sys.path.append(TOP_TESTS_DIR)

from pyobts.basicts import Result
from cgents import CgenTS
import pyobts.ucmd as ucmd


class CgenLexerTS(CgenTS):

    def __init__(self):
        super().__init__('cgen lexer')
        self.test_bin = os.path.join(self.build_dir, "bin/cgen-test-lexer")

    def run(self, t):
        self.get_test_details(t)


        ret, out, err = ucmd.run_cmd([self.test_bin, self.t_path_cg])
        valid = ret == 0
        if valid:
            return Result.Ok()
        else:
            err = err.decode('ascii', 'ignore')
            return Result.Err(err)

if __name__ == '__main__':
    ts = CgenLexerTS()
    valid = ts.run_all()
    sys.exit(0 if valid else 1)
