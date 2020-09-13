#ifndef FIRESTORM_LOGGING
#define FIRESTORM_LOGGING

#include "../include/splashkit/splashkit.h"
#include <chrono>
#include <ctime>

#include "response.h"

enum LogLevel {
  Debug,
  Warning,
  Error,
};

extern LogLevel _log_level;

void log(LogLevel level, string message);
void log(http_request request, Response response);

#endif
