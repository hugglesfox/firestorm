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
  vector<Route> routes;
  vector<MiddleWare> middlewares;
  void route(http_request request);
  Outcome handle_middlewares(http_request request);
  FireStorm add_route(string uri, RouteFn, http_method method);
  bool is_duplicate(Route r);

public:
  FireStorm get(string uri, RouteFn fn);
  FireStorm post(string uri, RouteFn fn);
  FireStorm del(string uri, RouteFn fn);
  FireStorm put(string uri, RouteFn fn);
  FireStorm middleware(MiddleWareFn fn, ErrorFn failure);
  void ignite(unsigned int port);
};

#endif
