#ifndef FIRESTORM_MIDDLEWARE_PARSE_URI_VARS
#define FIRESTORM_MIDDLEWARE_PARSE_URI_VARS

#include "../include/splashkit/splashkit.h"
#include <unordered_map>

#include "../utils.h"
#include "../middleware.h"

using UriVars = std::unordered_map<string, string>;

template <typename R> class ParseUriVars : public MiddleWare<R> {
private:
  UriVars path_vars(http_request request);
  UriVars arg_vars(http_request request);
  UriVars uri_vars(http_request request);
  bool matches(http_request request);

public:
  string uri;
  Outcome handle(R *route, http_request request);
};

#endif
