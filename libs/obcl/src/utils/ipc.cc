#include "utils/ipc.hh"
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <stdexcept>

namespace obcl {

IPC::IPC() : _running(false) {}

void IPC::run() {
  pid_t pid = fork();
  if (pid == -1)
    throw std::runtime_error{"IPC: failed to fork"};

  if (pid > 0) // parent
  {
    _pid = pid;
    _running = true;
    return;
  }

  // child
  const char *cmd = _cmd.c_str();
  std::vector<const char *> argv;
  argv.push_back(cmd);
  for (const auto &x : _args)
    argv.push_back(x.c_str());
  argv.push_back(nullptr);

  if (execv(cmd, (char **)&argv[0]) < 0) {
    std::cerr << "Failed to run command: " << strerror(errno) << std::endl;
    std::abort();
  }
}

void IPC::wait() {
  if (waitpid(_pid, &_status, 0) == -1)
    throw std::runtime_error{"IPC: failed to wait for child"};
  _running = false;
}

bool IPC::normal_exit() const { return WIFEXITED(_status); }

int IPC::retcode() const { return WEXITSTATUS(_status); }

} // namespace obcl
