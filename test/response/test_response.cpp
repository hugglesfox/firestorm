#include "catch.hpp"
#include "response.h"

TEST_CASE("test response") {
  Response response;
  response.content_type = "text/plain";
  response.status = HTTP_STATUS_OK;

  SECTION("test cookies") {
    response.add_cookie(Cookie("foo", "bar"));
    REQUIRE(response.headers.at(0) == "Set-Cookie: foo=bar; SameSite=Lax");
  }

  SECTION("test status") {
    REQUIRE(status(HTTP_STATUS_OK) == response);
  }

  SECTION("test plain") {
    response.body = "Hello World\n";
    REQUIRE(plain("Hello World") == response);
  }

  SECTION("test json") {
    response.content_type = "application/json";
    response.body = "{\n    \"hello\": \"world\"\n}\n";

    json body = create_json("{\"hello\": \"world\"}");
    REQUIRE(json_data(body) == response);
  }

  SECTION("test redirect") {
    response.content_type = "";
    response.status = HTTP_STATUS_SEE_OTHER;
    response.headers = {"Location: example.com"};
    REQUIRE(redirect("example.com") == response);
  }
}

