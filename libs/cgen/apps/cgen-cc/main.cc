#include "cgen-compiler.hh"
#include "obcl/utils/arguments.hh"
#include "obcl/utils/str.hh"
#include <iostream>

int main(int argc, char **argv) {

  obcl::Arguments args;
  args.add_flag("stage-parse", "Parse the input file");
  args.add_flag("stage-type", "Perform semantic analysis");
  args.add_flag("stage-ctranslate", "Run translation to C");
  args.add_flag("build-object", "Build object file (.o)");
  args.add_flag("build-binary", "Build binary file");
  args.add_flag("custom-ret-code",
                "Use specific return code depending on the error kind");
  args.add_flag("cc-debug", "Enable debug flags for the C Compiler");
  args.add_option("output", "Output file, or '-' for stdin, interpretation "
                            "depends on the stage option");
  args.add_option("cc-libs",
                  "Path of static/shared C libraries, separated by ';'");
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

  if (args.has_flag("cc-debug"))
    cc.set_cc_debug(true);

  if (args.has_flag("custom-ret-code"))
    cc.set_custom_ret_code(true);

  if (args.has_flag("stage-ctranslate")) {
    cc.do_ctranslate();
    if (args.has_option("output"))
      cc.set_output_c_file(args.get_option("output"));
  }

  if (args.has_flag("build-object")) {
    cc.do_build_object();
    if (args.has_option("output"))
      cc.set_output_object_file(args.get_option("output"));
  }

  if (args.has_flag("build-binary")) {
    cc.do_build_binary();
    if (args.has_option("output"))
      cc.set_output_binary_file(args.get_option("output"));
  }

  if (args.has_option("cc-libs")) {
    auto libs = obcl::str::split(args.get_option("cc-libs"), ';');
    for (const auto &lib : libs)
      cc.add_c_lib(lib);
  }

  cc.run();
  return 0;
}
