#include "router.h"

using namespace std;

// Checks to see if a string is a path variable identifier.
// If do then it returns the identifier name, otherwise returns an empty string.
string parse_identifier(string id) {
  if (id.length() > 2 && id.front() == '<' && id.back() == '>') {
    return id.substr(1, id.length() - 2);
  }

  return "";
}

// Splits a string at / ignoring arguments
vector<string> split_path(string uri) {
  string path = split_at(uri, '?').front();
  return split_at(path, '/');
}

// Split a string at & ignoring path
vector<string> split_args(string uri) {
  // The HTTP spec states that only the first ? should be considered
  string args = split_at_first(uri, '?').back();
  return split_at(args, '&');
}

// Returns an unordered map of the variable path identifiers and the correlating
// values from a request.
//
// For an example if the variable path was /animal/<animal>
// then the request /animal/dog
// would result in {"animal": "dog"} being returned.
UriArgs path_vars(http_request request, string uri) {
  UriArgs result;

  vector<string> request_stubs = request_uri_stubs(request);
  vector<string> path_stubs = split_path(uri);

  for (size_t i = 0; i < path_stubs.size(); i++) {
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
UriArgs arg_vars(http_request request, string uri) {
  UriArgs result;
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
UriArgs uri_vars(http_request request, string uri) {
  UriArgs result = path_vars(request, uri);
  UriArgs args = arg_vars(request, uri);

  result.insert(args.begin(), args.end());
  return result;
}

// Returns a boolean of whether a request matches a route.
bool uri_matches(http_request request, string uri) {
  // Handle variable paths
  vector<string> request_stubs = request_uri_stubs(request);
  vector<string> route_stubs = split_path(uri);

  if (request_stubs.size() != route_stubs.size()) {
    return false;
  }

  for (size_t i = 0; i < request_stubs.size(); i++) {
    // Handle a variable path segment
    string id = parse_identifier(route_stubs[i]);
    if (!(id.size() > 0 || request_stubs[i] == route_stubs[i])) {
      return false;
    }
  }
  return true;
}
