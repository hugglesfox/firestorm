#ifndef FIRESTORM_ROUTER
#define FIRESTORM_ROUTER

#include "splashkit.h"
#include <unordered_map>

#include "middleware.h"
#include "utils.h"

using UriArgs = std::unordered_map<string, string>;

UriArgs uri_vars(http_request request, string uri);
bool uri_matches(http_request request, string uri);

template <typename R> class Router : public MiddleWare<R> {
private:
  http_method method;
  vector<string> uris;

public:
  Router(http_method method, vector<string> uris) : method(method), uris(uris) {}

  Outcome outcome(R &route, http_request request) {
    for (string uri : uris) {
      if (request_method(request) == method && uri_matches(request, uri)) {
        route.uri_args = uri_vars(request, uri);
        return Outcome::Success;
      }
    }
    return Outcome::Failure;
  }
};

#endif
