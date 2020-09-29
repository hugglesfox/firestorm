#include "catch.hpp"
#include "firestorm_mock.h"

TEST_CASE("test uri vars parsing") {
  auto request = MockRequest()
                     .uri("/animals/dog?color=black")
                     .construct();

  REQUIRE(uri_vars(&request, "/animals/<animal>?<color>")["color"] == "black");
  REQUIRE(uri_vars(&request, "/animals/<animal>?<color>")["animal"] == "dog");
  REQUIRE(uri_vars(&request, "/").size() == 0);
}

TEST_CASE("test uri matches") {
  auto request = MockRequest()
                    .uri("/animals/dog?color=black")
                    .construct();

  REQUIRE(uri_matches(&request, "/animals/<animal>/?<color>"));
  REQUIRE(!uri_matches(&request, "/animals/animal>?<color"));
  REQUIRE(!uri_matches(&request, "/a"));
}
