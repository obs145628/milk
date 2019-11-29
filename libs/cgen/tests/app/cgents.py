import os
import sys
from pyobts.basicts import BasicTS

class CgenTS(BasicTS):

    def __init__(self, name):

        # Test options
        py_dir = os.path.dirname(os.path.realpath(__file__))
        samples_dir = os.path.join(py_dir, "../examples")
        build_dir = sys.argv[1]
        all_files = set(os.listdir(samples_dir))
        test_files = [os.path.splitext(x)[0] for x in all_files
                      if x.endswith('.cg')]
        test_filter = sys.argv[2] if len(sys.argv) >= 3 else None

        self.samples_dir = samples_dir
        self.build_dir = build_dir

        
        tests = list(test_files)
        if test_filter is not None:
            tests = [t for t in tests if test_filter in t]
        super().__init__(name, tests)

    def get_test_details(self, t):
        self.t_name = t
        self.t_name_cg = '{}.cg'.format(self.t_name)
        self.t_path_cg = os.path.join(self.samples_dir, self.t_name_cg)

        self.t_err = None
        if self.t_name.startswith('err_'):
            self.t_err = self.t_name.split('_')[1]
