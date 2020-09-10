#ifndef FIRESTORM_ROUTER
#define FIRESTORM_ROUTER

#include "include/splashkit/splashkit.h"
#include <unordered_map>

#include "middleware.h"
#include "utils.h"

using UriVars = std::unordered_map<string, string>;

template <typename R> class Router : public MiddleWare<R> {
private:
  http_method method;
  vector<string> uris;

  UriVars path_vars(http_request request, string uri);
  UriVars arg_vars(http_request request, string uri);
  UriVars uri_vars(http_request request, string uri);
  bool matches(http_request request, string uri);

public:
  Router(http_method method, vector<string> uris)
      : method(method), uris(uris) {}
  Outcome handle(R &route, http_request request);
};

#define FIRESTORM_ROUTER_FUNCTIONS
#include "router.cpp"

#endif
