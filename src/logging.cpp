#include "logging.h"

LogLevel _log_level = Debug;

void log(LogLevel level, string message) {
  // Set colors depending on log level
  switch (level) {
  case Debug:
    if (_log_level == Warning) {
      return;
    }
    write("DEBUG: ");
    break;
  case Warning:
    if (_log_level == Error) {
      return;
    }
    write("\033[0;33m");
    write("WARN: ");
    break;
  case Error:
    write("\033[0;31m");
    write("ERROR: ");
    break;
  }

  auto time = std::chrono::system_clock::now();
  std::time_t c_time = std::chrono::system_clock::to_time_t(time);
  string str_time = std::ctime(&c_time);
  // Required to remove the new line character ctime decides to add
  write(str_time.substr(0, str_time.length() - 1));
  write(" ");
  write(message);

  // No color
  write("\033[0m\n");
}

void log(http_request request, Response response) {
  LogLevel level;

  // Set the level based on the response
  switch (response.status) {
  case HTTP_STATUS_BAD_REQUEST:
  case HTTP_STATUS_UNAUTHORIZED:
  case HTTP_STATUS_FORBIDDEN:
  case HTTP_STATUS_NOT_FOUND:
  case HTTP_STATUS_METHOD_NOT_ALLOWED:
  case HTTP_STATUS_CONFLICT:
    level = Warning;
    break;
  case HTTP_STATUS_INTERNAL_SERVER_ERROR:
  case HTTP_STATUS_NOT_IMPLEMENTED:
  case HTTP_STATUS_SERVICE_UNAVAILABLE:
    level = Error;
    break;

  default:
    level = Debug;
    break;
  }

  string method;

  switch (request_method(request)) {
  case HTTP_GET_METHOD:
    method = "GET";
    break;
  case HTTP_POST_METHOD:
    method = "POST";
    break;
  case HTTP_PUT_METHOD:
    method = "PUT";
    break;
  case HTTP_DELETE_METHOD:
    method = "DELETE";
    break;
  case HTTP_OPTIONS_METHOD:
    method = "OPTIONS";
    break;
  case HTTP_TRACE_METHOD:
    method = "TRACE";
    break;
  default:
    method = "UNK";
    break;
  }

  int code = static_cast<int>(response.status);

  log(level, method + " " + std::to_string(code) + " " + request_uri(request));
}
