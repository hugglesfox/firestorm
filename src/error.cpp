#include "error.h"

ErrorFn Error::from(http_status_code status) {
  switch (status) {
  case HTTP_STATUS_BAD_REQUEST:
    return bad_request;
  case HTTP_STATUS_UNAUTHORIZED:
    return unauthorized;
  case HTTP_STATUS_FORBIDDEN:
    return forbidden;
  case HTTP_STATUS_NOT_FOUND:
    return not_found;
  case HTTP_STATUS_METHOD_NOT_ALLOWED:
    return method_not_allowed;
  case HTTP_STATUS_CONFLICT:
    return conflict;

  case HTTP_STATUS_INTERNAL_SERVER_ERROR:
    return internal_server_error;
  case HTTP_STATUS_NOT_IMPLEMENTED:
    return not_implemented;
  case HTTP_STATUS_SERVICE_UNAVAILABLE:
    return service_unavailable;

  default:
    return internal_server_error;
  }
}

// Default error handlers

Response bad_request_fn() {
  return plain("Bad Request", HTTP_STATUS_BAD_REQUEST);
}

Response unauthorized_fn() {
  return plain("Unauthorized", HTTP_STATUS_UNAUTHORIZED);
}

Response forbidden_fn() { return plain("Forbidden", HTTP_STATUS_FORBIDDEN); }

Response not_found_fn() { return plain("Not Found", HTTP_STATUS_NOT_FOUND); }

Response method_not_allowed_fn() {
  return plain("Method Not Allowed", HTTP_STATUS_METHOD_NOT_ALLOWED);
}

Response conflict_fn() { return plain("Conflict", HTTP_STATUS_CONFLICT); }

Response internal_server_error_fn() {
  return plain("Internal Server Errror", HTTP_STATUS_INTERNAL_SERVER_ERROR);
}

Response not_implemented_fn() {
  return plain("Not Implemented", HTTP_STATUS_NOT_IMPLEMENTED);
}
Response service_unavailable_fn() {
  return plain("Service Unavailable", HTTP_STATUS_SERVICE_UNAVAILABLE);
}
