#include "milk/compiler/compiler.hh"
#include "obcl/utils/arguments.hh"
#include "obcl/utils/str.hh"
#include <iostream>

int main(int argc, char **argv) {

  obcl::Arguments args;
  args.add_flag("stage-parse", "Parse the input file");
  args.run(argc, (const char **)argv);
  if (args.other().size() < 1) {
    std::cerr << "Missing input file" << std::endl;
    return 10;
  }

  milk::Compiler cl;
  auto in_file = args.other().front();

  if (args.has_flag("stage-parse")) {
    cl.parse_file(in_file);
  }

  return 0;
}
