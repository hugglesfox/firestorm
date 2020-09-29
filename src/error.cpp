#include "error.h"


void HttpError::register_handler(http_status_code status, const Response &response) {
  handlers[status] = response;
}

Response HttpError::from(http_status_code status) {
  if (handlers.count(status) > 0) {
    return handlers.at(status);
  }

  return plain(std::to_string(static_cast<int>(status)), status);
}

