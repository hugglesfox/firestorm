#ifndef FIRESTORM_MOCK
#define FIRESTORM_MOCK

#include "firestorm.h"
#include "utils.h"

struct _http_request_data {
  int id = 0x48524551;
  string uri;
  string query_string;
  http_method method;

  unsigned short port;
  string body;
  string filename;
  vector<string> headers;
};

class MockRequest {
private:
  _http_request_data request;

public:
  MockRequest add_header(string header);
  MockRequest add_cookie(Cookie cookie);
  MockRequest uri(string uri);
  MockRequest body(string body);
  MockRequest body(json body);
  MockRequest method(http_method method);
  _http_request_data construct();
};

#endif
