#ifndef FIRESTORM_ROUTER_FUNCTIONS
#include "router.h"
#else

// Returns an unordered map of the variable path identifiers and the correlating
// values from a request.
//
// For an example if the variable path was /animal/<animal>
// then the request /animal/dog
// would result in {"animal": "dog"} being returned.
template <typename R> UriVars Router<R>::path_vars(http_request request) {
  UriVars result;

  vector<string> request_stubs = request_uri_stubs(request);
  vector<string> path_stubs = split_path(uri);

  for (int i = 0; i < path_stubs.size(); i++) {
    string id = parse_identifier(path_stubs[i]);

    if (id.length() > 0) {
      result[id] = request_stubs[i];
    }
  }

  return result;
}

// Returns an un ordered map of the variable argument identifiers and the
// correlating value from a request.
//
// For an example if the variable path was /animal?<name>
// then the request /animal?name=spot
// would result in {"name": "spot"} being returned.
template <typename R> UriVars Router<R>::arg_vars(http_request request) {
  UriVars result;
  vector<string> arg_vars = split_args(uri);

  for (string &var : arg_vars) {
    string id = parse_identifier(var);

    if (id.length() > 0) {
      result[id] = request_query_parameter(request, id, "");
    }
  }

  return result;
}

// Returns a combination of path_vars() and arg_vars()
template <typename R> UriVars Router<R>::uri_vars(http_request request) {
  UriVars result = path_vars(request);
  UriVars args = arg_vars(request);

  result.insert(args.begin(), args.end());
  return result;
}

// Returns a boolean of whether a request matches a route.
template <typename R> bool Router<R>::matches(http_request request) {
  // Handle variable paths
  vector<string> request_stubs = request_uri_stubs(request);
  vector<string> route_stubs = split_path(uri);

  if (request_stubs.size() != route_stubs.size()) {
    return false;
  }

  for (int i = 0; i < request_stubs.size(); i++) {
    // Handle a variable path segment
    string id = parse_identifier(route_stubs[i]);
    if (!(id.size() > 0 || request_stubs[i] == route_stubs[i])) {
      return false;
    }
  }
  return true;
}

template <typename R>
Outcome Router<R>::handle(R &route, http_request request) {
  if (request_method(request) == method && matches(request)) {
    route.args = uri_vars(request);
    return Outcome::Success;
  }
  return Outcome::Failure;
}

#endif
