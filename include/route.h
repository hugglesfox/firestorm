#ifndef FIRESTORM_ROUTE
#define FIRESTORM_ROUTE

#include "splashkit.h"
#include <memory>

#include "response.h"
#include "outcome.h"

class Route {
public:
  http_request _request;
  virtual ~Route() {}
  virtual Outcome middlewares() { return Outcome::Success; };
  virtual Response response() { throw HTTP_STATUS_INTERNAL_SERVER_ERROR; }
};

#endif
