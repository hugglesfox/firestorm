#ifndef FIRESTORM
#define FIRESTORM

#include "include/splashkit/splashkit.h"
#include "response.h"
#include "routing.h"
#include <unordered_map>

class FireStorm {
private:
  vector<Route> routes;
  void route(http_request request);

public:
  FireStorm get(string path, const RouteFn &fn);
  // FireStorm post(RouteFn fn);
  // FireStorm del(RouteFn fn);
  // FireStorm put(RouteFn fn);
  void ignite(unsigned int port);
};

#endif
