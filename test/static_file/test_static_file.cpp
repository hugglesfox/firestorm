#include "catch.hpp"
#include "static_file.h"

TEST_CASE("test detect file type") {
  REQUIRE(file_type("index.txt") == "text/plain");
}
