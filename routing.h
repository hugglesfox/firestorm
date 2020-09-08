#ifndef FIRESTORM_ROUTING
#define FIRESTORM_ROUTING

#include "include/splashkit/splashkit.h"

#include "middlewares/parse_uri_vars.h"
#include "response.h"

class Route {
protected:
  virtual vector<MiddleWare<Route>> middlewares() { return {}; };

public:
  UriVars vars;
  Outcome<Response> handle(http_request request);
  virtual Outcome<Response> route() { throw HTTP_STATUS_NOT_FOUND; }
};

#endif
