#include "utils.h"

// Split a string at a character.
// If the string starts with character being split, there will be an empty
// string in the 0th position of the returned array.
// This isn't a bug, it's a feature!
std::vector<std::string> split_at(std::string s, char c) {
  std::vector<std::string> parts;
  std::string part;

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
