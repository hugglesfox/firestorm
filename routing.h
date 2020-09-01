#ifndef FIRESTORM_ROUTING
#define FIRESTORM_ROUTING

#include "include/splashkit/splashkit.h"
#include "response.h"
#include "unordered_map"

using RouteFn = Response (*)(std::unordered_map<string, string> path);
using PathVars = std::unordered_map<string, string>;

struct Route {

  string path;
  http_method method;
  RouteFn fn;

  bool matches(http_request request);
  Response route(http_request request);
  PathVars path_vars(http_request request);
};

#endif
