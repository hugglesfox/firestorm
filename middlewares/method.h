#ifndef FIRESTORM_MIDDLEWARE_METHOD
#define FIRESTORM_MIDDLEWARE_METHOD

#include "../include/splashkit/splashkit.h"
#include "../middleware.h"

template <typename R> class Method : public MiddleWare<R> {
private:
  http_method method;

public:
  Method(http_method method) : method(method) {}
  Outcome handle(R &route, http_request request);
};

#include "method.cpp"

#endif
