#ifndef FIRESTORM_HTML
#define FIRESTORM_HTML

#include "splashkit.h"
#include <unordered_map>

#include "utils.h"

using HtmlVars = std::unordered_map<string, string>;

string parse_html(string filename, HtmlVars args);

#endif
