//===-- utils/arguments.hh - Arguments class definition ----=----*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the Arguments class
///
//===----------------------------------------------------------------------===//

#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

namespace obcl {

/// Helper class for command-line arguments
/// Check if arguments is valid
/// Easy access to arguments
/// Print formatted help message
class Arguments {
public:
  /// Must be called before run
  /// Add a value option, of the form --<name> <val>
  /// @param desc Description of the option, displayed with print_help()
  /// @param base the default value is none is set. If empty, there is no
  /// default value
  void add_option(const std::string &name, const std::string &desc,
                  const std::string &base = {});

  /// Must be called before run
  /// Add an option without value, it's only a boolean.
  /// of the form --<mame>
  /// @param desc Description of the flag, displayed with print_help()
  void add_flag(const std::string &name, const std::string &desc);

  /// Parse the arguments
  /// exit with an error if arguments are invalid
  /// or exit normally for the help option
  void run(int argc, const char **argv);

  /// @returns the whole list of arguments (with argv[0])
  /// Must be called after run
  const std::vector<std::string> &all() const { return _args; }

  /// @returns all the arguments that are not options
  /// Must be called after run
  std::vector<std::string> other() const;

  /// @returns true if a flag option (--<name>) is activated
  /// Must be called after run
  bool has_flag(const std::string &name) const;

  /// @returns true if an option (--<name> --val) is set, or if it has a default
  /// value
  /// Must be called after run
  bool has_option(const std::string &name) const;

  /// @returns the value of an option (--<name> --val), or it's default value
  /// Must be called after run, and has_option(name) must be true
  const std::string &get_option(const std::string &name) const;

  /// print a formatted message with the CLI usage
  /// Must be called after run
  void print_help() const;

private:
  struct OptionsInfos {
    std::string desc;
    std::string base; // not used for flags
  };

  std::vector<std::string> _args;
  std::vector<int> _used;
  std::map<std::string, OptionsInfos> _def_opts;
  std::map<std::string, OptionsInfos> _def_flags;
  std::map<std::string, std::string> _opts;
  std::set<std::string> _flags;

  void _parse_opts();
  void _parse_flags();

  bool _run_called() const;
};

} // namespace obcl
