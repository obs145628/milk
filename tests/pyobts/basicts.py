import sys


class Result:

    def __init__(self, ok, err):
        self.ok = ok
        self.err = err

    @staticmethod
    def Ok():
        return Result(True, None)

    @staticmethod
    def Err(err):
        return Result(False, err)



class BasicTS:

    def __init__(self, name, tests_list):
        self.name = name
        self.tests_list = tests_list
        self.max_tname_len = max([len(t) for t in self.tests_list])
        self.ntests = len(self.tests_list)
        self.nsuccs = 0

    def run_all(self):

        intro_line = '=== Test Suite: {} ==='.format(self.name)
        print(intro_line)

        for t in self.tests_list:
            self.run_one(t)
        

        print('{}: Results: {}/{} ({}%)'.format(self.name,
                                                self.nsuccs,
                                                self.ntests,
                                                100 * self.nsuccs/self.ntests))
            
            
        print('=' * len(intro_line))

        return self.nsuccs == self.ntests
        

    def run_one(self, t):    
        sys.stdout.write('{}...{}'.format(t, ' ' * (self.max_tname_len - len(t) + 3)))
        sys.stdout.flush()
        
        res = self.run(t)
        if res.ok:
            self.nsuccs += 1
            print('[OK]')
        else:
            print('[KO]')
            print(res.err)

    def run(self):
        raise Exception('BasicTS::run() Not implemented')
