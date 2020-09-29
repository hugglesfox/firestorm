#include "firestorm_mock.h"

MockRequest MockRequest::add_header(string header) {
  request.headers.push_back(header);
  return *this;
}

MockRequest MockRequest::add_cookie(Cookie cookie) {
  request.headers.push_back(cookie.construct());
  return *this;
}

MockRequest MockRequest::body(string body) {
  request.body = body;
  return *this;
};

MockRequest MockRequest::body(json body) {
  request.body = json_to_string(body);
  return *this;
}

MockRequest MockRequest::method(http_method method) {
  request.method = method;
  return *this;
}

MockRequest MockRequest::uri(string uri) {
  request.uri = uri;
  request.query_string = split_at_first(uri, '?').back();
  return *this;
}

// Construct a http_request from a MockRequest
_http_request_data MockRequest::construct() {
  return request;
}
