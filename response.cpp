#include "response.h"
#include "include/splashkit/splashkit.h"

// Send response the to the client
void Response::send(http_request request) {
  send_response(request, status, body, content_type);
}

Response status(http_status_code status) {
  return Response {status, {}, "text/plain", ""};
}

Response plain(string text, http_status_code status) {
  return Response {status, {}, "text/plain", text};
}
