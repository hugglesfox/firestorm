#ifndef FIRESTORM_STATIC_FILE
#define FIRESTORM_STATIC_FILE

#include "splashkit.h"

#include "middleware.h"
#include "route.h"
#include "router.h"
#include "utils.h"

string file_type(string filename);

class StaticFile : public Route {
private:
  string filename;
  string path;
  string content_type;

public:
  UriArgs uri_args;

  StaticFile(string filename, string path, string content_type)
      : filename(filename), path(path), content_type(content_type) {}

  StaticFile(string filename, string path)
      : filename(filename), path(path) {
        content_type = file_type(filename);
      }

  Outcome middlewares() {
    return MiddleWares<StaticFile>()
        .add(new Router<StaticFile>(HTTP_GET_METHOD, {path + filename}))
        .outcome(*this);
  }

  Response response() { return file(filename, content_type); }
};

#endif
