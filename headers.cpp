#include "headers.h"

// Constructs a Headers type from a http_request
Headers headers(http_request request) {
  Headers result;
  for (string header : request_headers(request)) {
    // Only the first : should be considered
    vector<string> parts = split_at_first(header, ':');
    result[parts.front()] = result[parts.back()];
  }
  return result;
}
