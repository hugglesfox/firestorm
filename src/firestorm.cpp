#include "firestorm.h"

void sigint(int signal) { exit(0); }

// Route a request
Response FireStorm::route(http_request request) {
  for (Route *route : routes) {
    try {
      route->_request = request;
      if (route->middlewares() != Outcome::Failure) {
        return route->response();
      }
    } catch (http_status_code s) {
      return error.from(s);
    } catch (...) {
      return error.from(HTTP_STATUS_INTERNAL_SERVER_ERROR);
    }
  }
  return error.from(HTTP_STATUS_NOT_FOUND);
}

// Register a route
FireStorm FireStorm::add_route(Route *route) {
  routes.push_back(route);
  return *this;
}

FireStorm FireStorm::error_handler(http_status_code status, const ErrorFn &handler) {
  error.register_handler(status, handler());
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
        (split_at_first(host_header, ':').front() == "127.0.0.1"
         && host == "localhost")) {
      route(request).send(request);
    }
  }
}
