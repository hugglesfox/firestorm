#ifndef FIRESTORM_ERROR
#define FIRESTORM_ERROR

#include "splashkit.h"
#include <unordered_map>

#include "response.h"

using ErrorFn = Response (*)();

class HttpError {
private:
  std::unordered_map<http_status_code, Response> handlers;

public:
  Response from(http_status_code status);
  void register_handler(http_status_code status, const Response &response);
};

#endif
