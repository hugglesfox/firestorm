#include "static_file.h"

string file_type(string filename) {
  string file_ext = split_at(filename, '.').back();

  if (file_ext == "ico") {
    return "image/vnd.microsoft.icon";
  }

  string extentions[] = {"css", "html", "js"};

  for (string extention : extentions) {
    if (file_ext == extention) {
      return "text/" + extention;
    }
  }

  return "text/plain";
}
