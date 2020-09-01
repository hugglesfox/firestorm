#ifndef FIRESTORM_MIDDLEWARE
#define FIRESTORM_MIDDLEWARE

#include "include/splashkit/splashkit.h"

#include "error.h"
#include "routing.h"

enum Outcome {
  Success,
  Failure,
};

using MiddleWareFn = Outcome (*)(http_request request);

struct MiddleWare {
  MiddleWareFn handler;
  ErrorFn failure;
};

#endif
