#include "html.h"

// Gets all the variable identifers in a template
vector<string> get_vars(string html) {
  vector<string> result;

  for (auto it = html.begin(); it < html.end(); it++) {
    if (*it == '{') {
      string id;
      while (*it != '}') {
        id.push_back(*it);
        it++;
      }

      id.push_back('}');
      result.push_back(id);
    }
  }
  return result;
}

// Strips the {} off of identifiers
string strip_identifier(string id) {
  return id.substr(1, id.length() - 2);
}

// Replace all the variables in a template with the values in vars
string parse_html(string filename, HtmlVars vars) {
  string html = file_as_string(filename, SERVER_RESOURCE);

  for (string id : get_vars(html)) {
    // If the variable isn't in vars, leave it alone
    if (vars.count(strip_identifier(id)) != 0) {
      int i = html.find(id);
      html.replace(i, id.length(), "");
      html.insert(i, vars[strip_identifier(id)]);
    }
  }

  return html;
}
