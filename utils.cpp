#include "utils.h"

using namespace std;

// Split a string at a character
vector<string> split_at(string s, char c) {
  stringstream is;
  is.str(s);

  string part;
  vector<string> parts;

  while (getline(is, part, c)) {
    if (part != "") {
      parts.push_back(part);
    }
  }

  return parts;
}
