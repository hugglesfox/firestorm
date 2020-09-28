#include "catch.hpp"
#include "form.h"

TEST_CASE("test parse form") {
  string form = "hello=world&foo=bar";

  REQUIRE(parse_form(form)["hello"] == "world");
  REQUIRE(parse_form(form)["foo"] == "bar");
}
