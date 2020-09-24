#include "catch.hpp"
#include "../src/utils.cpp"
#include "../src/static_file.cpp"

TEST_CASE("test detect file type") {
  REQUIRE(file_type("index.txt") == "text/plain");
}
