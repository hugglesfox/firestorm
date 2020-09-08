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
        return;
      } catch (http_status_code s) {
        error.from(s)().send(request);
        return;
      } catch (...) {
        error.internal_server_error().send(request);
        return;
      }
    }
  }
  error.not_found().send(request);
}

// Handle middlewares
Outcome FireStorm::handle_middlewares(http_request request) {
  for (MiddleWare middleware : middlewares) {
    try {
      if (middleware.handler(request) == Outcome::Failure) {
        middleware.failure().send(request);
        return Outcome::Failure;
      }
    } catch (http_status_code s) {
      error.from(s)().send(request);
      return Outcome::Failure;
    } catch (...) {
      error.internal_server_error().send(request);
      return Outcome::Failure;
    }
  }
  return Outcome::Success;
}

// Register a route
FireStorm FireStorm::add_route(Route *route) {
  routes.push_back(route);
  return *this;
}

// Error register error handler
FireStorm FireStorm::bad_request(ErrorFn fn) {
  error.bad_request = fn;
  return *this;
}

FireStorm FireStorm::unauthorized(ErrorFn fn) {
  error.unauthorized = fn;
  return *this;
}

FireStorm FireStorm::forbidden(ErrorFn fn) {
  error.forbidden = fn;
  return *this;
}

FireStorm FireStorm::not_found(ErrorFn fn) {
  error.not_found = fn;
  return *this;
}

FireStorm FireStorm::method_not_allowed(ErrorFn fn) {
  error.method_not_allowed = fn;
  return *this;
}

FireStorm FireStorm::internal_server_error(ErrorFn fn) {
  error.internal_server_error = fn;
  return *this;
}

FireStorm FireStorm::not_implemented(ErrorFn fn) {
  error.not_implemented = fn;
  return *this;
}

FireStorm FireStorm::service_unavailable(ErrorFn fn) {
  error.service_unavailable = fn;
  return *this;
}

// Register a middleware that will either always throw or always succeed
FireStorm FireStorm::middleware(MiddleWareFn fn) {
  MiddleWare middleware = {fn, error.internal_server_error};
  middlewares.push_back(middleware);
  return *this;
}

// Register a middleware with a custom failure handler
FireStorm FireStorm::middleware(MiddleWareFn fn, ErrorFn failure) {
  MiddleWare middleware = {fn, failure};
  middlewares.push_back(middleware);
  return *this;
}

// Start the server
void FireStorm::ignite(unsigned int port) {
  web_server server = start_web_server(port);
  while (true) {
    signal(SIGINT, sigint);
    http_request request = next_web_request(server);

    // Don't route the request if a middleware failed otherwise it'll try
    // sending 2 responses to the same request which creates unpredictable
    // behaviour.
    if (handle_middlewares(request) == Outcome::Success) {
      route(request);
    }
  }
}
