#include "bincl/compiler.hh"
#include "utils/ipc.hh"
#include <cassert>

namespace {
const char *DEFAULT_CC = "/usr/bin/gcc";
}

namespace obcl {

namespace bin {

Compiler::Compiler() : _bin_path(DEFAULT_CC), _debug(DebugMode::NO) {}

void Compiler::build_object(const std::string &in_src,
                            const std::string &out_obj) {
  std::vector<std::string> args;
  _add_cl_options(args);
  args.push_back("-c");
  args.push_back(in_src);
  args.push_back("-o");
  args.push_back(out_obj);
  _run_cl(args);
}

void Compiler::build_bin(const std::vector<std::string> &in_src,
                         const std::string &out_bin) {
  std::vector<std::string> args;
  _add_cl_options(args);
  args.insert(args.end(), in_src.begin(), in_src.end());
  args.push_back("-o");
  args.push_back(out_bin);
  args.insert(args.end(), _static_libs.begin(), _static_libs.end());
  _run_cl(args);
}

void Compiler::add_lib(const std::string &path) {
  _static_libs.push_back(path);
}

void Compiler::_add_cl_options(std::vector<std::string> &args) const {
  switch (_debug) {
  case DebugMode::NO:
    break;
  case DebugMode::L1:
    args.push_back("-g1");
    break;
  case DebugMode::L2:
    args.push_back("-g2");
    break;
  case DebugMode::L3:
    args.push_back("-g3");
    break;
  }
}

void Compiler::_run_cl(const std::vector<std::string> &args) const {
  IPC cmd;
  cmd.set_cmd(_bin_path);
  cmd.set_args(args);
  cmd.run();
  cmd.wait();
  int ret = cmd.retcode();
  assert(ret == 0);
}

} // namespace bin
} // namespace obcl
