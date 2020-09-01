#include "firestorm.h"
#include "include/splashkit/splashkit.h"

using namespace std;

void sigint(int signal) { exit(0); }

// Route a request
void FireStorm::route(http_request request) {
  for (Route route : routes) {
    if (route.matches(request)) {
      try {
        route.route(request).send(request);
      } catch (...) {
        // 500
        plain("Internal server error", HTTP_STATUS_INTERNAL_SERVER_ERROR)
            .send(request);
      }
      return;
    }
  }
  // 404
  plain("Not found", HTTP_STATUS_NOT_FOUND).send(request);
}

// Returns a boolean of whether a route has already been defined at that uri
bool FireStorm::is_duplicate(string uri) {
  for (Route route : routes) {
    if (route.uri == uri) {
      return true;
    }
  }
  return false;
}

// Register a get route
FireStorm FireStorm::get(string uri, RouteFn fn) {
  if (!is_duplicate(uri)) {
    Route route = {uri, HTTP_GET_METHOD, fn};
    routes.push_back(route);
    return *this;
  }
   throw std::invalid_argument("Duplicate route: " + uri);
}

// Start the server
void FireStorm::ignite(unsigned int port) {
  web_server server = start_web_server(port);
  while (true) {
    signal(SIGINT, sigint);
    http_request request = next_web_request(server);
    route(request);
  }
}
