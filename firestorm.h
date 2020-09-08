#ifndef FIRESTORM
#define FIRESTORM

#include "include/splashkit/splashkit.h"
#include <unordered_map>
#include <csignal>

#include "response.h"
#include "routing.h"
#include "utils.h"
#include "error.h"
#include "middleware.h"

class FireStorm {
private:
  Error error;
  vector<Route*> routes;
  void route(http_request request);
  bool is_duplicate(Route r);

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
