#ifndef FIRESTORM_ROUTER
#define FIRESTORM_ROUTER

#include "include/splashkit/splashkit.h"

#include "middleware.h"
#include "utils.h"

template <typename R> class Router : public MiddleWare<R> {
private:
  http_method method;
  vector<string> uris;

public:
  Router(http_method method, vector<string> uris)
      : method(method), uris(uris) {}

  Outcome handle(R &route, http_request request) {
    for (string uri : uris) {
      if (request_method(request) == method && uri_matches(request, uri)) {
        route.args = uri_vars(request, uri);
        return Outcome::Success;
      }
    }
    return Outcome::Failure;
  }
};

#endif
