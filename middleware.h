#ifndef FIRESTORM_MIDDLEWARE
#define FIRESTORM_MIDDLEWARE

#include "include/splashkit/splashkit.h"
#include "error.h"

enum OutcomeKind {
  Success,
  Failure,
};

template <typename R> struct Outcome {
  OutcomeKind kind;
  R route;
};

template <typename R> class MiddleWare {
public:
  virtual Outcome<R> handle(http_request request) {
    throw HTTP_STATUS_INTERNAL_SERVER_ERROR;
  }
};

#endif
