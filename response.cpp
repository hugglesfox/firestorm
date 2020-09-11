#include "response.h"

// Send response the to the client
void Response::send(http_request request) {
  send_response(request, status, body, content_type, headers);
}

Response status(http_status_code status) {
  return Response{status, {}, "text/plain"};
}

Response plain(string text, http_status_code status) {
  return Response{status, {}, "text/plain", text + "\n"};
}

Response json_data(json data, http_status_code status) {
  return Response{status, {}, "application/json", json_to_string(data) + "\n"};
}

Response redirect(string location) {
  return Response{HTTP_STATUS_SEE_OTHER, {"Location: " + location}};
}
