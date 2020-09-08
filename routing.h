#ifndef FIRESTORM_ROUTING
#define FIRESTORM_ROUTING

#include "include/splashkit/splashkit.h"

#include "middlewares/parse_uri_vars.h"
#include "response.h"
#include "utils.h"

class Route {
public:
  vector<MiddleWare<Route>> middlewares = {};
  UriVars vars;
  virtual Response route() { throw HTTP_STATUS_NOT_FOUND; }
};

#endif
