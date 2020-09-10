#include "utils.h"

using namespace std;

// Split a string at a character.
// If the string starts with character being split, there will be an empty
// string in the 0th position of the returned array.
// This isn't a bug, it's a feature!
vector<string> split_at(string s, char c) {
  vector<string> parts;
  string part;

  for (char character : s) {
    if (character != c) {
      part += character;
    } else if (!part.empty()) {
      parts.push_back(part);
      part = "";
    }
  }
  parts.push_back(part);
  return parts;
}

// Checks to see if the inputted string is a path variable identifier.
// If do then it returns the identifier name, otherwise returns an empty string.
string parse_identifier(string id) {
  if (id.length() > 2 && id[0] == '<' && id[id.length() - 1]) {
    return id.substr(1, id.length() - 2);
  }

  return "";
}

// Splits a string at / ignoring arguments
vector<string> split_path(string uri) {
  string path = split_at(uri, '?')[0];
  return split_at(path, '/');
}

// Split a string at & ignoring path
vector<string> split_args(string uri) {
  vector<string> uri_parts = split_at(uri, '?');

  // Remove the path bit
  uri_parts.front() = uri_parts.back();
  uri_parts.pop_back();

  // The HTTP spec states that only the first ? has any significance
  string args;
  for (string arg : uri_parts) {
    args += '?' + arg;
  }
  args.erase(0, 1);

  return split_at(args, '&');
}
