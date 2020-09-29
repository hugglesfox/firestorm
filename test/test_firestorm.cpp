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

class FormParsing : public Route {
public:
  FormData form_data;

  Outcome middlewares() {
    return MiddleWares<FormParsing>()
      .add(new Form<FormParsing>())
      .outcome(*this);
  }
};

class BadRoute : public Route {
public:
  Response response() {
    throw "Blah";
  }
};

TEST_CASE("test default error handling") {
  auto request = MockRequest().uri("/").construct();

  SECTION("test default route") {
    FireStorm firestorm = FireStorm().add_route(new Route());
    REQUIRE(firestorm.route(&request) == firestorm.error.from(HTTP_STATUS_INTERNAL_SERVER_ERROR));
  }

  SECTION("test default middleware") {
    FireStorm firestorm = FireStorm().add_route(new DefaultMiddleWare());
    REQUIRE(firestorm.route(&request) == firestorm.error.from(HTTP_STATUS_INTERNAL_SERVER_ERROR));
  }

  SECTION("test error catching") {
    FireStorm firestorm = FireStorm().add_route(new BadRoute());
    REQUIRE(firestorm.route(&request) == firestorm.error.from(HTTP_STATUS_INTERNAL_SERVER_ERROR));
  }
}

TEST_CASE("test hello") {
  FireStorm firestorm = FireStorm().add_route(new Hello());

  SECTION("test routing") {
    auto request = MockRequest().uri("/hello/world?age=old").construct();
    REQUIRE(firestorm.route(&request) == plain("Hello world aged old"));
  }

  SECTION("test not found") {
    auto request = MockRequest().uri("/").construct();
    REQUIRE(firestorm.route(&request) == firestorm.error.from(HTTP_STATUS_NOT_FOUND));
  }
}

TEST_CASE("test form parser headers") {
  FireStorm firestorm = FireStorm().add_route(new FormParsing());

  SECTION("test correct content type") {
    auto request = MockRequest().add_header("Content-Type: application/x-www-form-urlencoded").construct();
    REQUIRE(firestorm.route(&request) != firestorm.error.from(HTTP_STATUS_NOT_FOUND));
  }

  SECTION("test incorrect content type") {
    auto request = MockRequest().construct();
    REQUIRE(firestorm.route(&request) == firestorm.error.from(HTTP_STATUS_NOT_FOUND));
  }
}

