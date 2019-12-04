#include "cgen-compiler.hh"
#include "obcl/utils/arguments.hh"
#include <iostream>

int main(int argc, char **argv) {

  obcl::Arguments args;
  args.add_flag("stage-parse", "Parse the input file");
  args.add_flag("stage-type", "Perform semantic analysis");
  args.add_flag("stage-ctranslate", "Run translation to C");
  args.add_option("output", "Output file, or '-' for stdin, interpretation "
                            "depends on the stage option");
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

  if (args.has_flag("stage-ctranslate")) {
    cc.do_ctranslate();
    if (args.has_option("output"))
      cc.set_output_c_file(args.get_option("output"));
  }

  cc.run();
  return 0;
}
