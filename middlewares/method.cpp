#include "method.h"

template <typename R> Outcome<R> Method<R>::handle(R route, http_request request) {
  if (request_method(request) == method) {
    return Outcome<R>{OutcomeKind::Success, route};
  }
  return Outcome<R>{OutcomeKind::Failure, route};
}
