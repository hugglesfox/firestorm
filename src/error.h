#ifndef FIRESTORM_ERROR
#define FIRESTORM_ERROR

#include "response.h"

using ErrorFn = Response (*)();

// Default error handlers
// 4xx
Response bad_request_fn();
Response unauthorized_fn();
Response forbidden_fn();
Response not_found_fn();
Response method_not_allowed_fn();
Response conflict_fn();

// 5xx
Response internal_server_error_fn();
Response not_implemented_fn();
Response service_unavailable_fn();

struct Error {
  // 4xx
  ErrorFn bad_request = bad_request_fn;
  ErrorFn unauthorized = unauthorized_fn;
  ErrorFn forbidden = forbidden_fn;
  ErrorFn not_found = not_found_fn;
  ErrorFn method_not_allowed = method_not_allowed_fn;
  ErrorFn conflict = conflict_fn;

  // 5xx
  ErrorFn internal_server_error = internal_server_error_fn;
  ErrorFn not_implemented = not_implemented_fn;
  ErrorFn service_unavailable = service_unavailable_fn;

  ErrorFn from(http_status_code status);
};

#endif
