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

// Handle middlewares
Outcome FireStorm::handle_middlewares(http_request request) {
  for (MiddleWare middleware : middlewares) {
    try {
      if (!middleware.handler(request).is_success()) {
        middleware.failure().send(request);
        return Outcome::Failure;
      }
    } catch (...) {
      // 500
      plain("Internal server error", HTTP_STATUS_INTERNAL_SERVER_ERROR)
          .send(request);
      return Outcome::Failure;
    }
  }
  return Outcome::Success;
}

// Returns a boolean of whether a route already exists
bool FireStorm::is_duplicate(Route r) {
  for (Route route : routes) {
    if (route.uri == r.uri && route.method == r.method) {
      return true;
    }
  }
  return false;
}

// Register a route
FireStorm FireStorm::add_route(string uri, RouteFn fn, http_method method) {
  Route route = {uri, method, fn};
  if (!is_duplicate(route)) {
    routes.push_back(route);
    return *this;
  }
  throw std::invalid_argument("Duplicate route: " + uri);
}

// Register a get route
FireStorm FireStorm::get(string uri, RouteFn fn) {
  return add_route(uri, fn, HTTP_GET_METHOD);
}

// Register a post route
FireStorm FireStorm::post(string uri, RouteFn fn) {
  return add_route(uri, fn, HTTP_POST_METHOD);
}

// Start the server
void FireStorm::ignite(unsigned int port) {
  web_server server = start_web_server(port);
  while (true) {
    signal(SIGINT, sigint);
    http_request request = next_web_request(server);
    if (handle_middlewares(request).is_success()) {
      route(request);
    }
  }
}
