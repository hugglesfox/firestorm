#include "../../src/firestorm.h"

class Hello : public Route {
public:
  UriArgs uri_args;

  Outcome middlewares() {
    return MiddleWares<Hello>()
        .add(new Router<Hello>(HTTP_GET_METHOD, {"/hello/<name>"}))
        .outcome(*this);
  }

  Response response() {
    return html("hello.html", {{"name", uri_args["name"]}}, HTTP_STATUS_OK);
  }
};

int main() {
  FireStorm().add_route(new Hello()).ignite(5000);
  return 0;
}
