#include "headers.h"

// Constructs a Headers type from a http_request
Headers headers(http_request request) {
  Headers result;
  for (string header : request_headers(request)) {
    // Only the first : should be considered
    vector<string> parts = split_at_first(header, ':');
    string name = parts.front();
    result[name] = trim(parts.back());
  }
  return result;
}

// Constructs a Cookies type from http_request
Cookies cookies(http_request request) {
  Cookies result;
  string cookies = headers(request)["Cookie"];
  for (string cookie : split_at(cookies, ';')) {
    vector<string> parts = split_at(trim(cookie), '=');
    result[parts.front()] = parts.back();
  }
  return result;
}
