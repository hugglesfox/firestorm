#ifndef FIRESTORM_UTILS
#define FIRESTORM_UTILS

#include "include/splashkit/splashkit.h"
#include <string>
#include <vector>

vector<string> split_at(string s, char c);
string parse_identifier(string id);
vector<string> split_args(string uri);
vector<string> split_path(string uri);

#endif
