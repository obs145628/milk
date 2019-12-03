#include "cgen-compiler.hh"
#include "obcl/utils/arguments.hh"
#include <iostream>

int main(int argc, char **argv) {

  obcl::Arguments args;
  args.add_flag("stage-parse", "Parse the input file");
  args.add_flag("stage-type", "Perform semantic analysis");
  args.run(argc, (const char **)argv);
  if (args.other().size() < 1) {
    std::cerr << "Missing input file" << std::endl;
    return 10;
  }
  CGenCompiler cc;

  auto input = args.other();
  for (const auto &f : input)
    cc.add_input_file(f);

  if (args.has_flag("stage-parse"))
    cc.do_parse();
  if (args.has_flag("stage-type"))
    cc.do_type();

  cc.run();
  return 0;
}
