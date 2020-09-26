#include "catch.hpp"
#include "firestorm_mock.h"
#include "../src/utils.h"
#include "../src/router.cpp"

TEST_CASE("test identifier parsing") {
  REQUIRE(parse_identifier("<name>") == "name");
  REQUIRE(parse_identifier("name>") == "");
  REQUIRE(parse_identifier("<name") == "");
  REQUIRE(parse_identifier("name") == "");
  REQUIRE(parse_identifier("<>") == "");
}

TEST_CASE("test path splitting") {
  REQUIRE(split_path("/hello/world") == vector<string> {"hello", "world"});
  REQUIRE(split_path("/") == vector<string> {""});
  REQUIRE(split_path("/hello?arg&another_arg") == vector<string> {"hello"});
  REQUIRE(split_path("/?&") == vector<string> {""});
}

TEST_CASE("test split args") {
  REQUIRE(split_args("/hello/world") == vector<string> {""});
  REQUIRE(split_args("/") == vector<string> {""});
  REQUIRE(split_args("/hello?arg&another_arg") == vector<string> {"arg", "another_arg"});
  REQUIRE(split_args("/?&") == vector<string> {"", ""});
}

TEST_CASE("test path vars parsing") {
  http_request request = MockRequest().uri("/animal/dog").construct();

  REQUIRE(path_vars(request, "/animal/<animal>?<color>")["animal"] == "dog");
  REQUIRE(path_vars(request, "/<animal>/<animal>")["animal"] == "dog");
  REQUIRE(path_vars(request, "/<segment>/<animal>").size() == 2);
  REQUIRE(path_vars(request, "/").size() == 0);
  REQUIRE(path_vars(request, "/animal/dog?<animal>").size() == 0);
}

TEST_CASE("test path args parsing") {
  http_request request = MockRequest()
                            .uri("/animals?animal=dog?&color=black")
                            .construct();

  REQUIRE(arg_vars(request, "/<animal>")["animal"] == "");
  REQUIRE(arg_vars(request, "/animals?<animal>&<color>")["animal"] == "dog?");
  REQUIRE(arg_vars(request, "/animals?<animal>&<color>")["color"] == "black");
  REQUIRE(arg_vars(request, "/animals?<animal>")["animal"] == "dog?");
  REQUIRE(arg_vars(request, "/animals?<color>")["color"] == "black");
  REQUIRE(arg_vars(request, "/?<animal>").size() == 1);
  REQUIRE(arg_vars(request, "/").size() == 0);
  REQUIRE(arg_vars(request, "/animal/dog").size() == 0);
}

TEST_CASE("test uri vars parsing") {
  http_request request = MockRequest()
                            .uri("/animals/dog?color=black")
                            .construct();

  REQUIRE(uri_vars(request, "/animals/<animal>?<color>")["color"] == "black");
  REQUIRE(uri_vars(request, "/animals/<animal>?<color>")["animal"] == "dog");
}

TEST_CASE("test uri matches") {
  http_request request = MockRequest()
                            .uri("/animals/dog?color=black")
                            .construct();

  REQUIRE(uri_matches(request, "/animals/<animal>?<color>"));
  REQUIRE(!uri_matches(request, "/animals/animal?<color>"));
  REQUIRE(!uri_matches(request, "/foo/animal?<color>"));
  REQUIRE(!uri_matches(request, "/?<color>"));
  REQUIRE(!uri_matches(request, "/"));
}
