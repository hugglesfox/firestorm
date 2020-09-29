#include "catch.hpp"
#include "headers.h"
#include "firestorm_mock.h"

TEST_CASE("test headers") {
   auto request = MockRequest()
                    .add_header("Host: 127.0.0.1")
                    .add_cookie(Cookie("foo", "bar"))
                    .add_cookie(Cookie("hello", "world"))
                    .construct();

  SECTION("test header parsing") {
    REQUIRE(headers(&request)["Host"] == "127.0.0.1");
  }

  SECTION("test cookie parsing") {
    REQUIRE(cookies(&request)["foo"] == "bar");
  }
}

