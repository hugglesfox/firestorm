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
  vector<Route *> routes;

public:
  HttpError error;
  FireStorm add_route(Route *route);
  FireStorm log_level(LogLevel level);
  FireStorm error_handler(http_status_code status, const ErrorFn &handler);
  Response route(http_request request);

  void ignite(unsigned int port = 5000, string host = "localhost");
};

#endif
