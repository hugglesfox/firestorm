#ifndef FIRESTORM_MOCK
#define FIRESTORM_MOCK

#include "firestorm.h"
#include "utils.h"

struct _http_request_data {
  int id = 0x48524551;
  string uri;
  string query_string;
  http_method method;
  string body;
  vector<string> headers;
};

class MockRequest {
private:
  string _uri;
  string _args;
  string _body;
  http_method _method;
  vector<string> headers;

public:
  MockRequest add_header(string header);
  MockRequest add_cookie(Cookie cookie);
  MockRequest uri(string uri);
  MockRequest body(string body);
  MockRequest body(json body);
  MockRequest method(http_method method);
  http_request construct();
};

#endif
