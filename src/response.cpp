#include "response.h"
#include "logging.h"

// Send response the to the client
void Response::send(http_request request) {
  log(request, *this);
  send_response(request, status, body, content_type, headers);
}

// Add a cookie to the response
Response Response::add_cookie(Cookie cookie) {
  headers.push_back(cookie.construct());
  return *this;
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

Response html(string filename, HtmlVars vars, http_status_code status) {
  return Response{status, {}, "text/html", parse_html(filename, vars)};
}

Response file(string filename, string content_type) {
  return Response{HTTP_STATUS_OK,
                  {},
                  content_type,
                  file_as_string(filename, SERVER_RESOURCE)};
}

Response redirect(string location) {
  return Response{HTTP_STATUS_SEE_OTHER, {"Location: " + location}};
}
