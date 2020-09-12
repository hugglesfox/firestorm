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
  vector<string> parts = split_at(s, c);

  string first = parts.front();
  parts.erase(parts.begin());

  string result;
  for (string part : parts) {
    result += c + part;
  }

  result.erase(0, 1);

  return {first, result};
}

// Checks to see if a string is a valid identifier (basically a string which
// is wrapped in the character spcified)
// If so then it returns the identifier name, otherwise returns an empty string.
string parse_identifier(string s, char left, char right) {
  if (s.length() > 2 && s.front() == left && s.back() == right) {
    return s.substr(1, s.length() - 2);
  }

  return "";
}
