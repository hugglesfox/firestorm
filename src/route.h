#ifndef FIRESTORM_ROUTING
#define FIRESTORM_ROUTING

#include "../include/splashkit/splashkit.h"
#include <memory>

#include "response.h"
#include "outcome.h"

class Route {
public:
  http_request request;
  virtual Outcome middlewares() { return Outcome::Success; };
  virtual Response route() { throw HTTP_STATUS_NOT_FOUND; }
};

#endif
