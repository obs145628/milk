#include "bincl/compiler.hh"
#include <catch2/catch.hpp>
#include <cstdlib>
#include <fstream>
#include <string>

namespace {

std::string read_file(const std::string &path) {
  std::ifstream is(path);
  is.seekg(0, std::ios::end);
  std::size_t size = is.tellg();
  is.seekg(0);

  std::string res;
  res.resize(size);
  is.read(&res[0], size);
  return res;
}

void write_file(const std::string &path, const std::string &content) {
  std::ofstream os(path);
  os.write(&content[0], content.size());
}

const char *C_HELLO_WORLD = "#include <stdio.h>\n"
                            "int main() {\n"
                            "printf(\"Hello, World !\\n\");\n"
                            "return 0;\n"
                            "}\n";

const char *TMP_SRC = "/tmp/obcl_test_helloworld.c";
const char *TMP_OBJ = "/tmp/obcl_test_helloworld.o";
const char *TMP_OUT = "/tmp/obcl_test_helloworld.out";
const char *TMP_OUTPUT = "/tmp/obcl_test_helloworld.res";
} // namespace

TEST_CASE("Test ocbl::bin::Compiler object", "[obcl_bin_compiler_object") {

  write_file(TMP_SRC, C_HELLO_WORLD);
  obcl::bin::Compiler cc;
  cc.build_object(TMP_SRC, TMP_OBJ);
}

TEST_CASE("Test ocbl::bin::Compiler bin", "[obcl_bin_compiler_bin") {
  write_file(TMP_SRC, C_HELLO_WORLD);
  obcl::bin::Compiler cc;
  cc.build_bin({TMP_SRC}, TMP_OUT);

  auto run_cmd = std::string(TMP_OUT) + " > " + std::string(TMP_OUTPUT);
  REQUIRE(std::system(run_cmd.c_str()) == 0);
  REQUIRE(read_file(TMP_OUTPUT) == "Hello, World !\n");
}
