#include "form.h"

// Parse a url encoded form
FormData parse_form(string data) {
  FormData result;

  for (string field : split_at(data, '&')) {
    vector<string> parts = split_at(field, '=');
    string name = parts.front();
    result[name] = parts.back();
  }

  return result;
}
