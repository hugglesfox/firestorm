#ifndef FIRESTORM_HEADERS
#define FIRESTORM_HEADERS

#include "include/splashkit/splashkit.h"
#include <unordered_map>

#include "utils.h"

using Headers = std::unordered_map<string, string>;

Headers headers(http_request request);

#endif
