#ifndef FIRESTORM_UTILS
#define FIRESTORM_UTILS

#include "include/splashkit/splashkit.h"
#include <string>
#include <unordered_map>
#include <vector>

using UriVars = std::unordered_map<string, string>;

vector<string> split_at(string s, char c);

string parse_identifier(string id);
vector<string> split_args(string uri);
vector<string> split_path(string uri);

UriVars path_vars(http_request request, string uri);
UriVars arg_vars(http_request request, string uri);
UriVars uri_vars(http_request request, string uri);
bool uri_matches(http_request request, string uri);

#endif
