#include "../src/firestorm.h"

// Create the route Hello
class Hello : public Route {
public:
  // uri_args is a hashmap of strings containing variable identifiers and their
  // corresponding values
  UriArgs uri_args;

  // Register middlewares to process requests
  Outcome middlewares() {
    return MiddleWares<Hello>()
        // Add the built in Router middleware to process get requests on the
        // paths /hello and /hello/<name>?<age>
        .add(new Router<Hello>(HTTP_GET_METHOD, {"/hello/<name>?<age>"}))
        .outcome(*this);
  }

  // Create a response to return to the client
  Response route() {
    return plain("Hello " + uri_args["name"] + " aged " + uri_args["age"],
                 HTTP_STATUS_OK);
  }
};

int main() {
  // Register the Hello route and run the web server on port 5000
  FireStorm().add_route(new Hello()).ignite(5000);
  return 0;
}
