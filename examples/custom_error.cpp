#include "firestorm.h"

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

Response not_found() {
  return plain("Nothing to see here...");
}

int main() {
  FireStorm().add_route(new Hello()).error_handler(HTTP_STATUS_NOT_FOUND, not_found).ignite();
  return 0;
}
