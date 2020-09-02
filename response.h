#ifndef FIRESTORM_RESPONSE
#define FIRESTORM_RESPONSE

#include "include/splashkit/splashkit.h"

struct Response {
  http_status_code status;
  vector<string> headers;
  string content_type;
  string body;

  void send(http_request request);
};

Response status(http_status_code status);
Response plain(string text, http_status_code status);
Response json_data(json data, http_status_code status);

#endif
