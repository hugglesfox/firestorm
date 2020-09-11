#include "headers.h"

Headers headers(http_request request) {
  Headers result;
  for (string header : request_headers(request)) {
    write_line(header);
    vector<string> parts = split_at(header, ':');
    if (parts.size() == 2) {
      result[parts[0]] = result[parts[1]];
    }
  }

  return result;
}
