from .testsuite import UnitTest
import os

class FilesTestFinder:

    def __init__(self):
        self.filters = []
        self.dirs = []

    def add_filter(self, f):
        self.filters += [f]

    def add_filter_endswith(self, s):
        self.filters += [lambda x : x.endswith(s)]
        
    def list_recur(self, d):
        res = []
        
        for root, dirs, files in os.walk(d):
            for name in files:
                f = os.path.join(root, name)
                if self.is_valid_file(f):
                    res += [f]
            
        return res
            

    def list_notrecur(self, d):
        res = []
        for name in os.listdir(d):
            f = os.path.join(d, name)
            if os.path.isfile(f) and self.is_valid_file(f):
                res += [f]
        return res

    def add_dir(self, d, recursive=False):
        self.dirs += [(d, recursive)]

    

    def find(self):
        res = []
        for d, recursive in self.dirs:
            files = self.list_recur(d) if recursive else self.list_notrecur(d)
            res += [self.get_unit(f) for f in files]

        return res


    def get_unit(self, f):
        f = os.path.abspath(f)
        name = os.path.basename(f)
        return UnitTest(name, f)

    def is_valid_file(self, f):
        for ftr in self.filters:
            if not ftr(f):
                return False
        return True
