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
      } catch (http_status_code s) {
        error.from(s)().send(request);
      } catch (...) {
        error.internal_server_error().send(request);
      }
    } else {
      write_line("hits here");
      error.not_found().send(request);
    }
  }
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

// Register a put route
FireStorm FireStorm::put(string uri, RouteFn fn) {
  return add_route(uri, fn, HTTP_PUT_METHOD);
}

// Register a delete route
FireStorm FireStorm::del(string uri, RouteFn fn) {
  return add_route(uri, fn, HTTP_DELETE_METHOD);
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

// Register a middleware
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
