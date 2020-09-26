#include "catch.hpp"
#include "../src/utils.cpp"

TEST_CASE("test split at") {
  REQUIRE(split_at("foo bar", ' ') == vector<string> {"foo", "bar"});
  REQUIRE(split_at("foobar", ' ') == vector<string> {"foobar"});
  REQUIRE(split_at("", 'a') == vector<string> {""});
  REQUIRE(split_at("foobar", 'o') == vector<string> {"f", "", "bar"});
  REQUIRE(split_at("foobar", 'f') == vector<string> {"", "oobar"});
  REQUIRE(split_at("foobar", 'r') == vector<string> {"fooba", ""});
}

TEST_CASE("test split at first") {
  REQUIRE(split_at_first("foobar", 'o') == vector<string> {"f", "obar"});
  REQUIRE(split_at_first("foobar", 'f') == vector<string> {"", "oobar"});
  REQUIRE(split_at_first("foobar", 'r') == vector<string> {"fooba", ""});
  REQUIRE(split_at_first("foo b ar", ' ') == vector<string> {"foo", "b ar"});
}
