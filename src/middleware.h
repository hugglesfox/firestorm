#ifndef FIRESTORM_MIDDLEWARE
#define FIRESTORM_MIDDLEWARE

#include "../include/splashkit/splashkit.h"

#include "error.h"
#include "outcome.h"
#include "route.h"

template <typename R> class MiddleWare {
public:
  virtual ~MiddleWare<R>() {}

  // Get the outcome of a middleware
  virtual Outcome outcome(R &route, http_request request) {
    throw HTTP_STATUS_INTERNAL_SERVER_ERROR;
  }
};

// A helper object to make managing multiple middlewares easier
template <typename R> class MiddleWares {
private:
  vector<MiddleWare<R> *> middlewares;

public:
  // Add a middleware to manage
  MiddleWares<R> add(MiddleWare<R> *middleware) {
    middlewares.push_back(middleware);
    return *this;
  }

  // Get the outcome of all the middlewares for a route.
  // If any of the middlewares fails then returns an Outcome::Failure
  Outcome outcome(R &route) {
    for (MiddleWare<R> *middleware : middlewares) {
      if (middleware->outcome(route, route._request) == Outcome::Failure) {
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
