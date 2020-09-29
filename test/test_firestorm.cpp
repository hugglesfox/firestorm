#include "catch.hpp"
#include "firestorm_mock.h"

class Hello : public Route {
public:
  UriArgs uri_args;

  Outcome middlewares() {
    return MiddleWares<Hello>()
        .add(new Router<Hello>(HTTP_GET_METHOD,
                               {"/hello", "/hello/<name>?<age>"}))
        .outcome(*this);
  }

  Response response() {
    return plain("Hello " + uri_args["name"] + " aged " + uri_args["age"]);
  }
};

class DefaultMiddleWare : public Route {
public:
  Outcome middlewares() {
    return MiddleWares<DefaultMiddleWare>()
         .add(new MiddleWare<DefaultMiddleWare>())
         .outcome(*this);
  }
};

class BadRoute : public Route {
public:
  Response response() {
    throw "Blah";
  }
};

TEST_CASE("test default route") {
  FireStorm firestorm = FireStorm().add_route(new Route());
  auto request = MockRequest().uri("/").construct();
  REQUIRE(firestorm.route(&request) == internal_server_error_fn());
}

TEST_CASE("test default middleware") {
  FireStorm firestorm = FireStorm().add_route(new DefaultMiddleWare());
  auto request = MockRequest().uri("/").construct();
  REQUIRE(firestorm.route(&request) == internal_server_error_fn());
}

TEST_CASE("test route error catching") {
  FireStorm firestorm = FireStorm().add_route(new BadRoute());
  auto request = MockRequest().uri("/").construct();
  REQUIRE(firestorm.route(&request) == internal_server_error_fn());
}

TEST_CASE("test hello") {
  FireStorm firestorm = FireStorm().add_route(new Hello());

  SECTION("test routing") {
    auto request = MockRequest().uri("/hello/world?age=old").construct();
    REQUIRE(firestorm.route(&request) == plain("Hello world aged old"));
  }

  SECTION("test not found") {
    auto request = MockRequest().uri("/").construct();
    REQUIRE(firestorm.route(&request) == not_found_fn());
  }
}


