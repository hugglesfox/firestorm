#ifndef FIRESTORM
#define FIRESTORM

#include "include/splashkit/splashkit.h"
#include "response.h"
#include "routing.h"
#include "utils.h"
#include <unordered_map>
#include <csignal>

class FireStorm {
private:
  vector<Route> routes;
  void route(http_request request);
  FireStorm add_route(string uri, RouteFn, http_method method);
  bool is_duplicate(Route r);

public:
  FireStorm get(string uri, RouteFn fn);
  FireStorm post(string uri, RouteFn fn);
  // FireStorm del(RouteFn fn);
  // FireStorm put(RouteFn fn);
  void ignite(unsigned int port);
};

#endif
