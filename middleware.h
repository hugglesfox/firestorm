#ifndef FIRESTORM_MIDDLEWARE
#define FIRESTORM_MIDDLEWARE

#include "include/splashkit/splashkit.h"

#include "error.h"

enum Outcome {
  Success,
  Failure,
};

template <typename R> class MiddleWare {
public:
  virtual Outcome handle(R route, http_request request) {
    throw HTTP_STATUS_INTERNAL_SERVER_ERROR;
  }
};

#endif
