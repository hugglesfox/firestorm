#include "firestorm_mock.h"

MockRequest MockRequest::add_header(string header) {
  headers.push_back(header);
  return *this;
}

MockRequest MockRequest::add_cookie(Cookie cookie) {
  headers.push_back(cookie.construct());
  return *this;
}

MockRequest MockRequest::body(string body) {
  _body = body;
  return *this;
};

MockRequest MockRequest::body(json body) {
  _body = json_to_string(body);
  return *this;
}

MockRequest MockRequest::method(http_method method) {
  _method = method;
  return *this;
}

MockRequest MockRequest::uri(string uri) {
  _uri = uri;
  _args = split_at_first(uri, '?').back();
  return *this;
}

// Construct a http_request from a MockRequest
http_request MockRequest::construct() {
  http_request request = new _http_request_data;
  request->uri = _uri;
  request->query_string = _args;
  request->method = _method;
  request->body = _body;
  request->headers = headers;

  return request;
}
