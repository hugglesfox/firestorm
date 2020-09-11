#include "../firestorm.h"

using namespace std;

// Create the route Hello
class Hello : public Route {
public:
  // uri_args is a hashmap of strings containing variable uri names and their
  // corresponding values
  UriArgs uri_args;

  // Register middlewares to process requests
  Outcome middlewares() {
    return MiddleWares<Hello>()
        // Add the built in Router middleware to process get requests on the
        // paths /hello and /hello/<name>?<age>
        .add(new Router<Hello>(HTTP_GET_METHOD,
                               {"/hello/<name>?<age>", "/hello"}))
        .outcome(*this);
  }

  // Create a response to return to the client
  Response route() {
    return plain("Hello " + uri_args["name"] + " aged " + uri_args["age"],
                 HTTP_STATUS_OK);
  }
};

int main() {
  // A FireStorm instance and run the web server on port 5000
  FireStorm().add_route(new Hello()).ignite(5000);

  return 0;
}
