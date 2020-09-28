#include "catch.hpp"
#include "utils.h"

TEST_CASE("test split at") {
  REQUIRE(split_at("foo bar", ' ') == vector<string> {"foo", "bar"});
}
