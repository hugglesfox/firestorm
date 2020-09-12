#ifndef FIRESTORM_MIDDLEWARE
#define FIRESTORM_MIDDLEWARE

#include "../include/splashkit/splashkit.h"

#include "error.h"
#include "outcome.h"
#include "route.h"

template <typename R> class MiddleWare {
public:
  virtual ~MiddleWare<R>() {}
  virtual Outcome handle(R &route, http_request request) {
    throw HTTP_STATUS_INTERNAL_SERVER_ERROR;
  }
};

template <typename R> class MiddleWares {
private:
  vector<MiddleWare<R> *> middlewares;

public:
  MiddleWares<R> add(MiddleWare<R> *middleware) {
    middlewares.push_back(middleware);
    return *this;
  }

  Outcome outcome(R &route) {
    for (MiddleWare<R> *middleware : middlewares) {
      if (middleware->handle(route, route.request) == Outcome::Failure) {
        delete middleware;
        return Outcome::Failure;
      }
      // Avoid a memory leak
      delete middleware;
    }
    return Outcome::Success;
  }
};

#endif
