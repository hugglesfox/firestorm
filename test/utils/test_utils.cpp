#include "catch.hpp"
#include "utils.h"

TEST_CASE("test split at") {
  REQUIRE(split_at("foo bar", ' ') == vector<string> {"foo", "bar"});
}

TEST_CASE("test split at first") {
  REQUIRE(split_at_first("foobar", 'o') == vector<string> {"f", "obar"});
}
