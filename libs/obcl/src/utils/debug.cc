#include "utils/debug.hh"
#include <cstdlib>
#include <iostream>

namespace obcl {

void panic_fn(const char *file, int line, const char *fun,
              const std::string &msg) {
  std::cerr << "Program panicked at " << fun << "(" << file << ":" << line
            << "): " << std::endl
            << msg << std::endl;
  std::exit(1);
}

} // namespace obcl
