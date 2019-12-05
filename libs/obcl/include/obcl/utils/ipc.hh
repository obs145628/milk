//===-- utils/ipc.hh - IPC class definition ---------------------*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definiton on the IPC Class (Inter-Process
/// Communication)
///
//===----------------------------------------------------------------------===//

#pragma once

#include <string>
#include <vector>

namespace obcl {

/// IPC (Interprocess Communication)
/// Start a new binary process
/// Can wait for it, and send / receive data
class IPC {

public:
  IPC();

  /// et the binary name (relative to the current program)
  void set_cmd(const std::string &cmd) { _cmd = cmd; }

  /// Set the program args (without program name)
  void set_args(const std::vector<std::string> &args) { _args = args; }

  // start running the program, non-blocking
  void run();

  /// wait until the program finished
  void wait();

  /// @returns true if the program exited normally
  /// must be called only after wait
  bool normal_exit() const;

  /// @return the return value of the program
  /// must be called only after wait
  int retcode() const;

private:
  bool _running;
  std::string _cmd;
  std::vector<std::string> _args;
  int _status;
  long _pid;
};

} // namespace obcl
