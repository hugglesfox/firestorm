#include "response.h"
#include "include/splashkit/splashkit.h"

void Response::send(http_request request) {
  send_response(request, status, body, content_type);
}

Response status(http_status_code status) {
  return Response {status, {}, "text/plain", ""};
}

Response plain(string text, http_status_code status) {
  return Response {status, {}, "text/plain", text};
}
