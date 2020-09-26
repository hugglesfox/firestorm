#include "utils.h"

// Split a string at a character.
// If the string starts with character being split, there will be an empty
// string in the 0th position of the returned array.
// This isn't a bug, it's a feature!
vector<string> split_at(string s, char c) {
  vector<string> result;
  size_t pos = 0;

  while ((pos = s.find(c)) != string::npos) {
    result.push_back(s.substr(0, pos));
    s.erase(0, pos + 1);
  }

  result.push_back(s);

  return result;
}

// Split at the first occurance of c
vector<string> split_at_first(string s, char c) {
  size_t pos = s.find(c);
  return {s.substr(0, pos), s.substr(pos + 1, s.back())};
}
