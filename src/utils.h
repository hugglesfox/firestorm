#ifndef FIRESTORM_UTILS
#define FIRESTORM_UTILS

#include "../include/splashkit/splashkit.h"

vector<string> split_at(string s, char c);
vector<string> split_at_first(string s, char c);

string parse_identifier(string s, char left, char right);

#endif
