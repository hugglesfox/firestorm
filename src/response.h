#ifndef FIRESTORM_RESPONSE
#define FIRESTORM_RESPONSE

#include "../include/splashkit/splashkit.h"

#include "cookie.h"
#include "html.h"

struct Response {
  http_status_code status;
  vector<string> headers;
  string content_type;
  string body;

  Response add_cookie(Cookie cookie);
  void send(http_request request);
};

Response status(http_status_code status);
Response plain(string text, http_status_code status);
Response json_data(json data, http_status_code status);
Response html(string filename, HtmlVars vars, http_status_code status);
Response file(string filename, string content_type);
Response redirect(string location);

#endif
