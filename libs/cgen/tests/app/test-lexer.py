import os
import sys
import subprocess

PY_DIR = os.path.dirname(os.path.realpath(__file__))
SAMPLES_DIR = os.path.join(PY_DIR, "../examples")
BUILD_DIR = sys.argv[1]
LEXER_TEST = os.path.join(BUILD_DIR, "bin/cgen-test-lexer")

ALL_FILES = set(os.listdir(SAMPLES_DIR))
TEST_FILES = [os.path.splitext(x)[0] for x in ALL_FILES
    if x.endswith('.cg')]

test_filter = sys.argv[2] if len(sys.argv) >= 3 else None


def run_cmd(cmd):
    p = subprocess.Popen(cmd,
        stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p.wait()
    out, err = p.communicate()
    ret = p.returncode
    return ret, out, err




def run_tests():

    ntests = 0
    nsuccs = 0

    print('Tests: Lexer')

    for t in TEST_FILES:
        tpath = os.path.join(SAMPLES_DIR, '{}.cg'.format(t))

        if test_filter and not test_filter in t:
            continue

        ntests += 1
        sys.stdout.write('{}... '.format(t))
        sys.stdout.flush()

        ret, out, err = run_cmd([LEXER_TEST, tpath])
        valid = ret == 0
        
        if valid:
            nsuccs += 1
            print('[OK]')
        else:
            print('[KO]')
            err = err.decode('ascii', 'ignore')
            print(err)

    print('Tests: Parser: {}/{} ({}%)'.format(nsuccs, ntests,
        100 * nsuccs/ntests))

run_tests()
