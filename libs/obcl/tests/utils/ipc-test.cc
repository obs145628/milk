#include "utils/ipc.hh"
#include <catch2/catch.hpp>

TEST_CASE("Test ocbl::IPC simple", "[obcl_ipc_simple") {

  {
    obcl::IPC cmd;
    cmd.set_cmd("/bin/ls");
    cmd.set_args({"-al", "."});
    cmd.run();
    cmd.wait();
    REQUIRE(cmd.normal_exit());
    REQUIRE(cmd.retcode() == 0);
  }

  {
    obcl::IPC cmd;
    cmd.set_cmd("/bin/true");
    cmd.run();
    cmd.wait();
    REQUIRE(cmd.normal_exit());
    REQUIRE(cmd.retcode() == 0);
  }

  {
    obcl::IPC cmd;
    cmd.set_cmd("/bin/false");
    cmd.run();
    cmd.wait();
    REQUIRE(cmd.normal_exit());
    REQUIRE(cmd.retcode() == 1);
  }
}
