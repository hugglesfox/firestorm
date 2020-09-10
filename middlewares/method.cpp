#include "method.h"

template <typename R>
Outcome Method<R>::handle(R *route, http_request request) {
  if (request_method(request) == method) {
    return Outcome::Success;
  }
  return Outcome::Failure;
}
