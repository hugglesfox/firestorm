#ifndef FIRESTORM_ROUTER_FUNCTIONS
#include "router.h"
#else

template <typename R>
Outcome Router<R>::handle(R &route, http_request request) {
  for (string uri : uris) {
    if (request_method(request) == method && uri_matches(request, uri)) {
      route.args = uri_vars(request, uri);
      return Outcome::Success;
    }
  }
  return Outcome::Failure;
}

#endif
