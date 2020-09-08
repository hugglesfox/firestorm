#ifndef FIRESTORM_MIDDLEWARE_METHOD
#define FIRESTORM_MIDDLEWARE_METHOD

#include "../include/splashkit/splashkit.h"
#include "../middleware.h"

template <typename R> class Method : public MiddleWare<R> {
  http_method method;

  Outcome<R> handle(R &route, http_request request);
};

#endif
