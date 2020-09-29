#include "catch.hpp"
#include "headers.h"
#include "firestorm_mock.h"

TEST_CASE("test headers") {
  auto request = MockRequest().add_header("Host: 127.0.0.1").construct();
  REQUIRE(headers(&request)["Host"] == "127.0.0.1");
}

TEST_CASE("test cookies") {
  auto request = MockRequest()
                    .add_cookie(Cookie("foo", "bar"))
                    .add_cookie(Cookie("hello", "world"))
                    .construct();

  REQUIRE(cookies(&request)["foo"] == "bar");
}

