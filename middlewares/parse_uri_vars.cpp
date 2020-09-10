#include "parse_uri_vars.h"

// Checks to see if the inputted string is a path variable identifier.
// If do then it returns the identifier name, otherwise returns an empty string.
template<typename R> string ParseUriVars<R>::parse_identifier(string id) {
  if (id.length() > 2 && id[0] == '<' && id[id.length() - 1]) {
    return id.substr(1, id.length() - 2);
  }

  return "";
}

// Splits a string at / ignoring arguments
template <typename R> vector<string> ParseUriVars<R>::split_path(string uri) {
  string path = split_at(uri, '?')[0];
  return split_at(path, '/');
}

// Split a string at & ignoring path
template <typename R> vector<string> ParseUriVars<R>::split_args(string uri) {
  vector<string> uri_parts = split_at(uri, '?');

  // Remove the path bit
  uri_parts.front() = uri_parts.back();
  uri_parts.pop_back();

  // The HTTP spec states that only the first ? has any significance
  string args;
  for (string arg : uri_parts) {
    args += '?' + arg;
  }
  args.erase(0, 1);

  return split_at(args, '&');
}

// Returns an unordered map of the variable path identifiers and the correlating
// values from a request.
//
// For an example if the variable path was /animal/<animal>
// then the request /animal/dog
// would result in {"animal": "dog"} being returned.
template <typename R> UriVars ParseUriVars<R>::path_vars(http_request request) {
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
template <typename R> UriVars ParseUriVars<R>::arg_vars(http_request request) {
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
template <typename R> UriVars ParseUriVars<R>::uri_vars(http_request request) {
  UriVars result = path_vars(request);

  UriVars args = arg_vars(request);
  result.insert(args.begin(), args.end());
  return result;
}

// Returns a boolean of whether a request matches a route.
template <typename R> bool ParseUriVars<R>::matches(http_request request) {
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
Outcome ParseUriVars<R>::handle(R &route, http_request request) {
  if (matches(request)) {
    route.args = arg_vars(request);
    return Outcome::Success;
  }

  return Outcome::Failure;
}
