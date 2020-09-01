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
UriVars Route::uri_vars(http_request request) {
  UriVars result;

  vector<string> request_stubs = request_uri_stubs(request);
  vector<string> route_stubs = split_path(uri);

  for (int i = 0; i < route_stubs.size(); i++) {
    string id = parse_identifier(route_stubs[i]);

    if (id.length() > 0) {
      result[id] = request_stubs[i];
    }
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
Response Route::route(http_request request) {
  return fn(path_vars(request));
}
