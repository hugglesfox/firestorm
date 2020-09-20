#ifndef TODO_MIDDLEWARE
#define TODO_MIDDLEWARE

#include "firestorm.h"
#include "models.h"

// A middleware to parse Todo objects from json request bodies
template <typename R> class ParseTodo : public MiddleWare<R> {
public:
  Outcome outcome(R &route, http_request request) {
    json body = json_from_string(request_body(request));

    if (json_has_key(body, "text") && json_has_key(body, "is_done")) {
      try {
        Todo todo = {json_read_string(body, "text"),
                     json_read_bool(body, "is_done")};
        route.body = todo;
      } catch (...) {
        throw HTTP_STATUS_BAD_REQUEST;
      }
      return Outcome::Success;
    }

    throw HTTP_STATUS_BAD_REQUEST;
  }
};

#endif
