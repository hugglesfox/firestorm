#ifndef FIRESTORM_MIDDLEWARE_PARSE_URI_VARS
#define FIRESTORM_MIDDLEWARE_PARSE_URI_VARS

#include "../include/splashkit/splashkit.h"
#include <unordered_map>

#include "../utils.h"
#include "../middleware.h"

using UriVars = std::unordered_map<string, string>;


template <typename R> class ParseUriVars : public MiddleWare<R> {
private:
  string uri;

  string parse_identifier(string id);
  vector<string> split_args(string uri);
  vector<string> split_path(string uri);

  UriVars path_vars(http_request request);
  UriVars arg_vars(http_request request);
  UriVars uri_vars(http_request request);
  bool matches(http_request request);

public:
  ParseUriVars(string uri) : uri(uri) {}

  Outcome handle(R &route, http_request request);
};

#include "parse_uri_vars.cpp"

#endif
