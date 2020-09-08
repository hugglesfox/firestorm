#include "routing.h"
#include "include/splashkit/splashkit.h"

using namespace std;

Outcome<Response> Route::handle(http_request request) {
  for (MiddleWare<Route> middleware : middlewares()) {
    Outcome<Route> outcome = middleware.handle(request);

  }
}
