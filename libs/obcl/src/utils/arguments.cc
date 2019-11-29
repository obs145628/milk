#include "utils/arguments.hh"
#include <cassert>
#include <cstdlib>
#include <iostream>

namespace obcl {

void Arguments::add_option(const std::string &name, const std::string &desc,
                           const std::string &base) {
  assert(!_run_called());
  assert(_def_opts.find(name) == _def_opts.end());

  OptionsInfos infos;
  infos.desc = desc;
  infos.base = base;
  _def_opts.emplace(name, infos);
}

void Arguments::add_flag(const std::string &name, const std::string &desc) {
  assert(!_run_called());
  assert(_def_flags.find(name) == _def_flags.end());

  OptionsInfos infos;
  infos.desc = desc;
  _def_flags.emplace(name, infos);
}

/// Parse the arguments
/// exit with an error if arguments are invalid
/// or exit normally for the help option
void Arguments::run(int argc, const char **argv) {
  assert(!_run_called());
  assert(argc > 0);
  add_flag("help", "Display usage infos");
  _args.reserve(argc);
  _used = std::vector<int>(argc, false);
  _used[0] = true;

  for (int i = 0; i < argc; ++i)
    _args.emplace_back(argv[i]);

  _parse_opts();
  _parse_flags();

  if (has_flag("help")) {
    print_help();
    std::exit(0);
  }
}

std::vector<std::string> Arguments::other() const {
  std::vector<std::string> res;
  for (std::size_t i = 0; i < _args.size(); ++i)
    if (!_used[i])
      res.push_back(_args[i]);
  return res;
}

/// @returns true if a flag option (--<name>) is activated
/// Must be called after run
bool Arguments::has_flag(const std::string &name) const {
  assert(_def_flags.find(name) != _def_flags.end());
  return _flags.find(name) != _flags.end();
}

/// @returns true if an option (--<name> --val) is set, or if it has a default
/// value
/// Must be called after run
bool Arguments::has_option(const std::string &name) const {
  auto def_it = _def_opts.find(name);
  auto it = _opts.find(name);
  assert(def_it != _def_opts.end());

  return it != _opts.end() || !def_it->second.base.empty();
}

/// @returns the value of an option (--<name> --val), or it's default value
/// Must be called after run, and has_option(name) must be true
const std::string &Arguments::get_option(const std::string &name) const {
  assert(has_option(name));
  auto def_it = _def_opts.find(name);
  auto it = _opts.find(name);

  return it == _opts.end() ? def_it->second.base : it->second;
}

/// print a formatted message with the CLI usage
void Arguments::print_help() const {
  assert(_run_called());
  std::cout << "Usage: " << _args.front() << " <argumnents...>" << std::endl
            << std::endl;

  for (const auto &def : _def_opts) {
    std::cout << "--" << def.first << " "
              << "<value>"
              << ": " << def.second.desc << std::endl;
    if (!def.second.base.empty())
      std::cout << "default value: " << def.second.base << std::endl;
    std::cout << std::endl;
  }

  for (const auto &def : _def_flags) {
    std::cout << "--" << def.first << ": " << def.second.desc << std::endl
              << std::endl;
  }
}

void Arguments::_parse_opts() {
  for (std::size_t i = 1; i + 1 < _args.size(); ++i) {
    if (_used[i])
      continue;
    const auto &arg = _args[i];

    if (arg.size() < 3 || arg[0] != '-' || arg[1] != '-')
      continue;

    auto key = arg.substr(2);
    if (_def_opts.find(key) == _def_opts.end()) {
      if (_def_flags.find(key) != _def_flags.end())
        continue;
      std::cerr << "CLI arguments: unknown option '" << key << "'" << std::endl;
      std::exit(10);
    }

    auto val = _args[i + 1];
    _opts.emplace(key, val);
    _used[i] = true;
    _used[i + 1] = true;
    ++i;
  }
}

void Arguments::_parse_flags() {
  for (std::size_t i = 1; i < _args.size(); ++i) {
    if (_used[i])
      continue;
    const auto &arg = _args[i];

    if (arg.size() < 3 || arg[0] != '-' || arg[1] != '-')
      continue;

    auto key = arg.substr(2);
    if (_def_flags.find(key) == _def_flags.end()) {
      if (_def_opts.find(key) != _def_opts.end())
        continue;
      std::cerr << "CLI arguments: unknown option '" << key << "'" << std::endl;
      std::exit(10);
    }

    _flags.emplace(key);
    _used[i] = true;
  }
}

bool Arguments::_run_called() const { return _args.size() > 0; }

} // namespace obcl
