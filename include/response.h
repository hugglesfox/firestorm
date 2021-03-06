#ifndef FIRESTORM_RESPONSE
#define FIRESTORM_RESPONSE

#include "splashkit.h"

#include "cookie.h"
#include "html.h"

struct Response {
  http_status_code status;
  vector<string> headers;
  string content_type;
  string body;

  Response add_cookie(Cookie cookie);
  void send(http_request request);

  bool operator ==(const Response &other) const {
    return this->status == other.status
      && this->headers == other.headers
      && this->content_type == other.content_type
      && this->body == other.body;
  }

  bool operator !=(const Response &other) const {
    return !(*this == other);
  }
};

Response status(http_status_code status);
Response plain(string text, http_status_code status = HTTP_STATUS_OK);
Response json_data(json data, http_status_code status = HTTP_STATUS_OK);
Response html(string filename, HtmlVars vars,
              http_status_code status = HTTP_STATUS_OK);
Response file(string filename, string content_type,
              http_status_code status = HTTP_STATUS_OK);
Response redirect(string location);

#endif
