#ifndef FIRESTORM
#define FIRESTORM

#include "../include/splashkit/splashkit.h"
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
#include "utils.h"


class FireStorm {
private:
  ErrorPages error;
  vector<Route *> routes;
  void route(http_request request);

public:
  FireStorm add_route(Route *route);
  FireStorm log_level(LogLevel level);

  FireStorm bad_request(ErrorFn fn);
  FireStorm unauthorized(ErrorFn fn);
  FireStorm forbidden(ErrorFn fn);
  FireStorm not_found(ErrorFn fn);
  FireStorm method_not_allowed(ErrorFn fn);
  FireStorm conflict(ErrorFn fn);

  FireStorm internal_server_error(ErrorFn fn);
  FireStorm not_implemented(ErrorFn fn);
  FireStorm service_unavailable(ErrorFn fn);

  void ignite(unsigned int port = 5000, string host = "localhost");
};

#endif
