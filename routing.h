#ifndef FIRESTORM_ROUTING
#define FIRESTORM_ROUTING

#include "include/splashkit/splashkit.h"
#include <memory>

#include "middlewares/parse_uri_vars.h"
#include "response.h"

class Route {
private:
  http_request request;

protected:
  template <typename R>
  Outcome use(R &route, vector<MiddleWare<R> *> middlewares) {
    for (MiddleWare<R> *middleware : middlewares) {
      if (middleware->handle(route, request) == Outcome::Failure) {
        return Outcome::Failure;
      }
    }

    return Outcome::Success;
  }

public:
  UriVars vars;

  void set_request(http_request request) { request = request; }
  virtual Outcome middlewares() { return Outcome::Success; };
  virtual Response route() { throw HTTP_STATUS_NOT_FOUND; }
};

#endif
