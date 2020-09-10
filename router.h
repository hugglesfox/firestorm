#ifndef FIRESTORM_ROUTER
#define FIRESTORM_ROUTER

#include "include/splashkit/splashkit.h"

#include "middleware.h"
#include "utils.h"


template <typename R> class Router : public MiddleWare<R> {
private:
  http_method method;
  vector<string> uris;

  public:
  Router(http_method method, vector<string> uris)
      : method(method), uris(uris) {}
  Outcome handle(R &route, http_request request);
};

#define FIRESTORM_ROUTER_FUNCTIONS
#include "router.cpp"

#endif
