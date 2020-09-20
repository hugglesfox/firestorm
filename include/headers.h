#ifndef FIRESTORM_HEADERS
#define FIRESTORM_HEADERS

#include "splashkit.h"
#include <unordered_map>

#include "utils.h"

using Headers = std::unordered_map<string, string>;
using Cookies = std::unordered_map<string, string>;

Headers headers(http_request request);
Cookies cookies(http_request request);

#endif
