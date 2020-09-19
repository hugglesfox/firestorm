#ifndef FIRESTORM_HTML
#define FIRESTORM_HTML

#include "splashkit.h"
#include <unordered_map>

#include "utils.h"

using HtmlVars = std::unordered_map<string, string>;

vector<string> get_vars(string html);
string strip_identifier(string id);
string parse_html(string filename, HtmlVars args);

#endif
