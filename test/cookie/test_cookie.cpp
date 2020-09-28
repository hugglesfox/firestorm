#include "catch.hpp"
#include "cookie.h"

TEST_CASE("test cookie header creation") {
  Cookie cookie = Cookie("foo", "bar");

  REQUIRE(cookie.construct() == "Set-Cookie: foo=bar; SameSite=Lax");

  SECTION("test max_age") {
    cookie.max_age = 10;

    REQUIRE(cookie.construct() == "Set-Cookie: foo=bar; Max-Age=10; SameSite=Lax");
  }

  SECTION("test secure") {
    cookie.secure = true;

    REQUIRE(cookie.construct() == "Set-Cookie: foo=bar; Secure; SameSite=Lax");
  }

  SECTION("test http_only") {
    cookie.http_only = true;

    REQUIRE(cookie.construct() == "Set-Cookie: foo=bar; HttpOnly; SameSite=Lax");
  }

  SECTION("test same_site Strict") {
    cookie.same_site = Strict;

    REQUIRE(cookie.construct() == "Set-Cookie: foo=bar; SameSite=Strict");
  }

  SECTION("test same_site Lax") {
    cookie.same_site = Lax;

    REQUIRE(cookie.construct() == "Set-Cookie: foo=bar; SameSite=Lax");
  }

  SECTION("test same_site None") {
    cookie.same_site = None;

    REQUIRE(cookie.construct() == "Set-Cookie: foo=bar; SameSite=None");
  }
}
