#include "static_file.h"

string file_type(string filename) {
  string ext = split_at(filename, '.').back();

  if (ext == "css") {
    return "text/css";
  }

  if (ext == "csv") {
    return "text/csv";
  }

  if (ext == "html" || ext == "htm") {
    return "text/html";
  }

  if (ext == "ico") {
    return "image/vnd.microsoft.icon";
  }

  if (ext == "js") {
    return "text/javascript";
  }

  if (ext == "json") {
    return "application/json";
  }

  if (ext == "xhtml") {
    return "application/xhtml+xml";
  }

  return "text/plain";
}
