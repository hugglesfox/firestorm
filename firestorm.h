#ifndef FIRESTORM
#define FIRESTORM

#include "include/splashkit/splashkit.h"
#include <csignal>
#include <unordered_map>

#include "error.h"
#include "middleware.h"
#include "response.h"
#include "route.h"
#include "utils.h"

class FireStorm {
private:
  Error error;
  vector<Route *> routes;
  void route(http_request request);

public:
  FireStorm add_route(Route *route);

  FireStorm bad_request(ErrorFn fn);
  FireStorm unauthorized(ErrorFn fn);
  FireStorm forbidden(ErrorFn fn);
  FireStorm not_found(ErrorFn fn);
  FireStorm method_not_allowed(ErrorFn fn);

  FireStorm internal_server_error(ErrorFn fn);
  FireStorm not_implemented(ErrorFn fn);
  FireStorm service_unavailable(ErrorFn fn);

  void ignite(unsigned int port);
};

#endif
