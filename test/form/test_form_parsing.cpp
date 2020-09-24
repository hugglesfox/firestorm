#include "catch.hpp"
#include "../src/utils.cpp"
#include "../src/form.cpp"

TEST_CASE("test parse form") {
  string form = "hello=world&foo=bar";

  REQUIRE(parse_form(form)["hello"] == "world");
  REQUIRE(parse_form(form)["foo"] == "bar");
}
