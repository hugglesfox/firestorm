#include "firestorm.h"

void sigint(int signal) { exit(0); }

// Route a request
void FireStorm::route(http_request request) {
  for (Route *route : routes) {
    try {
      route->_request = request;
      if (route->middlewares() != Outcome::Failure) {
        route->response().send(request);
        return;
      }
    } catch (http_status_code s) {
      error.from(s)().send(request);
      return;
    } catch (...) {
      error.internal_server_error().send(request);
      return;
    }
  }
  error.not_found().send(request);
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

// Set the logging level
FireStorm FireStorm::log_level(LogLevel level) {
  _log_level = level;
  return *this;
}

// Start the server on a port
void FireStorm::ignite(unsigned int port, string host) {
  web_server server = start_web_server(port);

  if (host == "127.0.0.1") {
    host = "localhost";
  }

  // Account for ports other then 80
  if (port != 80) {
    host += ":" + std::to_string(port);
  }

  write_line(
    "\033[1;33mFireStorm\033[0m web server running on http://" + host);

  while (true) {
    signal(SIGINT, sigint);
    http_request request = next_web_request(server);

    string host_header = headers(request)["Host"];

    // Only route the request if the host is correct
    if (host == "0.0.0.0" || host_header == host ||
        (host_header == "127.0.0.1" && host == "localhost")) {
      route(request);
    }
  }
}
