import subprocess

def run_cmd(cmd):
    p = subprocess.Popen(cmd,
        stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p.wait()
    out, err = p.communicate()
    ret = p.returncode
    return ret, out, err
