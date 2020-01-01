import sys


'''
Container class to get infos about the test
Only get a constructor for bulding
The test runner get this object, run the test, and fill the struct
'''
class UnitTest:

    STATE_WAIT = 1 #test waiting to be run
    STATE_RUN = 2 #test running
    STATE_OK = 3 #test runned successfully
    STATE_KO = 4 #tested runned and got an error

    def __init__(self, name, data=None):
        self.name = name #unique name identifier for the test
        self.data = data #Some opaque data needed to run the test. None if not relevant 
        self.state = UnitTest.STATE_WAIT #current state of the state
        self.err_id = None #int or word to indicate what error is it, None if test Ok or not relevant to this kind of test
        self.err_mes = None #a little message to tell the kind of error. None if test is ok
        self.err_short = None #a short description of what went wrong, a few lines. None if test if ok
        self.err_long = None #other informations relevant to the test. it is stored on files, not displayed. None is test is ok, or if not relevant



'''
Default implementation of a runner, for example sake
Must create it's own runner
'''
class TestRunner:

    def __init__(self):
        pass

    def run(self, t):
        t.state = UnitTest.STATE_KO
        t.err_mes = 'TestRunner not implemented'
        t.err_short = 'The test couldn\'t be run. Use a custom testrunner instead of the default'
        

class TestSuite:

    def __init__(self, name, tests, runner):
        self.name = name
        self.tests = tests
        self.runner = runner
        self.os = sys.stdout

    def err_ts(self, mess):
        sys.stderr.write('Error internal to the TestSuite: {}\n Aborting.\n'.format(mess))
        sys.exit(10)

    def run(self):

        if len(self.tests) == 0:
            self.os.write('TestSuite {} cannot be run: no tests found\n'.format(self.name))
            self.os.flush()
            return False
        
        self.max_tname_len = max([len(t.name) for t in self.tests])
        self.ntests = len(self.tests)
        self.nsuccs = 0
        
        intro_line = '=== Test Suite: {} ==='.format(self.name)
        self.os.write('{}\n'.format(intro_line))
        self.os.flush()

        for t in self.tests:
            self.run_one(t)

        self.os.write('{}: Results: {}/{} ({}%)\n'.format(self.name,
                                                          self.nsuccs,
                                                          self.ntests,
                                                          100 * self.nsuccs/self.ntests))
            
            
        self.os.write('{}\n'.format('=' * len(intro_line)))
        return self.nsuccs == self.ntests

    def run_and_exit(self):
        valid = self.run()
        sys.exit(0 if valid else 1)

    def run_one(self, t):
        name = t.name
        self.os.write('{}...{}'.format(name, ' ' * (self.max_tname_len - len(name) + 3)))
        self.os.flush()

        t.state = UnitTest.STATE_RUN
        self.runner.run(t)

        if t.state == UnitTest.STATE_OK:
            self.nsuccs += 1
            self.os.write('[OK]\n')
        elif t.state == UnitTest.STATE_KO:
            self.os.write('[KO]')
            if t.err_id is not None:
                self.os.write('[{}]'.format(t.err_id))

            if t.err_mes is None:
                self.err_ts('Expected error message for invalid test {}'.format(t.name))
            self.os.write(': {}\n'.format(t.err_mes))

            if t.err_short is None:
                self.err_ts('Expected short error description for invalid test {}'.format(t.name))
            self.os.write('{}\n'.format(t.err_short))

            #TODO: use t.err_long

        else:
            self.err_ts('Runner for {} left state invalid'.format(t.name))

        self.os.flush()
