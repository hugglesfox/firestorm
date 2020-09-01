#include "routing.h"
#include "include/splashkit/splashkit.h"

using namespace std;

// Checks to see if the inputted string is a path variable identifier.
// If do then it returns the identifier name, otherwise returns an empty string.
string parse_identifier(string id) {
  if (id[0] == '<' && id[id.length() - 1]) {
    return id.substr(1, id.length() - 2);
  }

  return "";
}

// Splits a string at / ignoring arguments
vector<string> split_path(string uri) {
  string path = split_at(uri, '?')[0];
  return split_at(path, '/');
}

vector<string> split_args(string uri) {
  string args = split_at(uri, '?')[1];
  return split_at(args, '&');
}

// Returns an unordered map of the variable path identifiers and the correlating
// values from a request.
//
// For an example if the variable path was /animal/<animal>
// then the request /animal/dog
// would result in {"animal": "dog"} being returned.
UriVars Route::path_vars(http_request request) {
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
UriVars Route::arg_vars(http_request request) {
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
UriVars Route::uri_vars(http_request request) {
  UriVars result = path_vars(request);

  if (method == HTTP_GET_METHOD) {
    UriVars args = arg_vars(request);
    result.insert(args.begin(), args.end());
  }

  return result;
}

// Returns a boolean of whether a request matches a route.
bool Route::matches(http_request request) {
  // Check request method
  if (method != request_method(request)) {
    return false;
  }

  // Check if the request matches directly
  // (it doesn't contain a variable path)
  if (uri == request_uri(request)) {
    return true;
  }

  // Handle variable paths
  vector<string> request_stubs = request_uri_stubs(request);
  vector<string> route_stubs = split_path(uri);

  for (int i = 0; i < request_stubs.size(); i++) {
    // Request path is longer then the route
    if (i >= route_stubs.size()) {
      return false;
    }

    // Handle a variable path segment
    string id = parse_identifier(route_stubs[i]);
    if (!(id.size() > 0 || request_stubs[i] == route_stubs[i])) {
      return false;
    }
  }

  return true;
}

// Handle a request using this route. Returns a Response.
Response Route::route(http_request request) { return fn(uri_vars(request)); }
