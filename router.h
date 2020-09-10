#ifndef FIRESTORM_ROUTER
#define FIRESTORM_ROUTER

#include "include/splashkit/splashkit.h"
#include <unordered_map>

#include "middleware.h"

using UriVars = std::unordered_map<string, string>;

vector<string> split_at(string s, char c);

string parse_identifier(string id);
vector<string> split_args(string uri);
vector<string> split_path(string uri);

UriVars path_vars(http_request request, string uri);
UriVars arg_vars(http_request request, string uri);
UriVars uri_vars(http_request request, string uri);
bool uri_matches(http_request request, string uri);

template <typename R> class Router : public MiddleWare<R> {
private:
  http_method method;
  vector<string> uris;

public:
  Router(http_method method, vector<string> uris)
      : method(method), uris(uris) {}

  Outcome handle(R &route, http_request request) {
    for (string uri : uris) {
      if (request_method(request) == method && uri_matches(request, uri)) {
        route.args = uri_vars(request, uri);
        return Outcome::Success;
      }
    }
    return Outcome::Failure;
  }
};

#endif
