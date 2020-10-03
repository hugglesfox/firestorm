#include "catch.hpp"
#include "static_file.h"

TEST_CASE("test detect file type") {
  REQUIRE(file_type("hello.txt") == "text/plain");
  REQUIRE(file_type("icon.ico") == "image/vnd.microsoft.icon");
  REQUIRE(file_type("index.html") == "text/html");
}
