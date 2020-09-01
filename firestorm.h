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
  bool is_duplicate(string uri);

public:
  FireStorm get(string path, RouteFn fn);
  FireStorm post(RouteFn fn);
  // FireStorm del(RouteFn fn);
  // FireStorm put(RouteFn fn);
  void ignite(unsigned int port);
};

#endif
