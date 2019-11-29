#include "cgen-compiler.hh"
#include "obcl/utils/arguments.hh"
#include <iostream>

int main(int argc, char **argv) {

  obcl::Arguments args;
  args.add_flag("stage-parse", "Parse the input file");
  args.run(argc, (const char **)argv);
  if (args.other().size() != 1) {
    std::cerr << "Missing input file" << std::endl;
    return 10;
  }
  CGenCompiler cc;

  auto input_file = args.other().front();
  cc.set_input_file(input_file);

  if (args.has_flag("stage-parse"))
    cc.do_parse();

  cc.run();
  return 0;
}
