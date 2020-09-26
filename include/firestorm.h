#ifndef FIRESTORM
#define FIRESTORM

#include "splashkit.h"
#include <csignal>

#include "cookie.h"
#include "error.h"
#include "form.h"
#include "headers.h"
#include "html.h"
#include "logging.h"
#include "middleware.h"
#include "outcome.h"
#include "response.h"
#include "route.h"
#include "router.h"
#include "static_file.h"

class FireStorm {
private:
  ErrorPages error;
  vector<Route *> routes;

public:
  FireStorm add_route(Route *route);
  FireStorm log_level(LogLevel level);

  FireStorm bad_request(const ErrorFn &fn);
  FireStorm unauthorized(const ErrorFn &fn);
  FireStorm forbidden(const ErrorFn &fn);
  FireStorm not_found(const ErrorFn &fn);
  FireStorm method_not_allowed(const ErrorFn &fn);
  FireStorm conflict(const ErrorFn &fn);

  FireStorm internal_server_error(const ErrorFn &fn);
  FireStorm not_implemented(const ErrorFn &fn);
  FireStorm service_unavailable(const ErrorFn &fn);

  Response route(http_request request);
  void ignite(unsigned int port = 5000, string host = "localhost");
};

#endif
