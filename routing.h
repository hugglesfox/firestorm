#ifndef FIRESTORM_ROUTING
#define FIRESTORM_ROUTING

#include "include/splashkit/splashkit.h"
#include <unordered_map>
#include "response.h"
#include "utils.h"

using UriVars = std::unordered_map<string, string>;
using RouteFn = Response (*)(UriVars path);

struct Route {

  string uri;
  http_method method;
  RouteFn fn;

  bool matches(http_request request);
  Response route(http_request request);
  UriVars uri_vars(http_request request);
  UriVars path_vars(http_request request);
  UriVars arg_vars(http_request request);
};

#endif
