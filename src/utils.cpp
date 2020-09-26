#include "utils.h"

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

// Split at the first occurance of c
vector<string> split_at_first(string s, char c) {
  size_t split = s.find(c);
  return {s.substr(0, split), s.substr(split + 1, s.back())};
}
