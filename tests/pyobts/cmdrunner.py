from .testsuite import UnitTest
from .ucmd import run_cmd

def read_file_bin(path):
    with open(path, "rb") as f:
        return f.read()

def write_file_bin(path, data):
    with open(path, 'wb') as f:
        f.write(data)
    

CHECKER_STR_SHORT = '''Invalid {} stream:
 --   actual:
<BEG>{}<END>
 -- expected:
<BEG>{}<END>'''

def checker_str(cmd_exp):

    def check(sname, cmd_out):
        cmd_out = cmd_out.decode('ascii', 'ignore')
        valid = cmd_out == cmd_exp
        err_short = None
        err_long = None

        if not valid:
            err_short = CHECKER_STR_SHORT.format(sname, cmd_out, cmd_exp)

        return valid, err_short, err_long

    return lambda s, x : check(s, x)

CHECKER_EMPTY_SHORT = '''Invalid {} stream. Should be empty, but contains:
<BEG>{}<END>'''

def checker_empty():

    def check(sname, cmd_out):
        valid = len(cmd_out) == 0
        err_short = None
        err_long = None

        if not valid:
            cmd_out = cmd_out.decode('ascii', 'ignore')
            err_short = CHECKER_EMPTY_SHORT.format(sname, cmd_out)

        return valid, err_short, err_long

    return lambda s, x : check(s, x)

CHECKER_FILE_SHORT = '''Invalid {} stream:
 --   actual:
<BEG>{}<END>
 -- file {}:
<BEG>{}<END>'''

def checker_file(exp_path):

    exp_bin = [None]

    def check(sname, cmd_out):
        if exp_bin[0] is None:
            exp_bin[0] = read_file_bin(exp_path)
        
        valid = exp_bin[0] == cmd_out
        err_short = None
        err_long = None

        if not valid:
            cmd_out = cmd_out.decode('ascii', 'ignore')
            cmd_exp = exp_bin[0].decode('ascii', 'ignore')
            err_short = CHECKER_FILE_SHORT.format(sname, cmd_out, exp_path, cmd_exp)

        return valid, err_short, err_long

    return lambda s, x : check(s, x)
        
    

class CmdTest:

    def __init__(self, path, args, exp_ret=None, check_out=None, check_err=None, out_save_path=None):
        self.cmd = [path] + list(args)
        self.exp_ret = exp_ret
        self.check_out =  check_out
        self.check_err = check_err
        self.out_save_path = out_save_path

    def run(self, t):

        cmd_ret, cmd_out, cmd_err = run_cmd(self.cmd)
        invalid = []
        all_err_short = []

        if self.exp_ret is not None and self.exp_ret != cmd_ret:
            invalid += ['return code']
            all_err_short += ['The command return code is {}, expected {}'.format(cmd_ret, self.exp_ret)]

        if self.check_out is not None:
            valid, err_short, err_long = self.check_out('output', cmd_out)
            if not valid:
                invalid += ['output stream']
                all_err_short += [err_short]

        if self.check_err is not None:
            valid, err_short, err_long = self.check_err('error', cmd_err)
            if not valid:
                invalid += ['error stream']
                all_err_short += [err_short]

        if len(invalid) > 0:
            t.err_mes = 'Command failed: invalid {}'.format(', '.join(invalid))
            t.err_short = 'Full command: {}\n{}\n'.format(' '.join(self.cmd), '\n'.join(all_err_short))
            return False

        if self.out_save_path is not None:
            write_file_bin(self.out_save_path, cmd_out)
        
        return True

class CmdRunner:

    def __init__(self, testsget):
        self.testsget = testsget
        pass

    def run(self, t):
        cmds = self.testsget(t.data)
        for cmd in cmds:
            if not cmd.run(t):
                t.state = UnitTest.STATE_KO
                return
            
        t.state = UnitTest.STATE_OK
