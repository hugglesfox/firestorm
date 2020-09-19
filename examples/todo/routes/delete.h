#ifndef TOOD_ROUTE_DELETE
#define TODO_ROUTE_DELETE

#include "firestorm.h"
#include "../middleware.h"
#include "../models.h"

// A route to delete a todo
class DeleteTodo : public Route {
public:
  UriArgs uri_args;
  vector<Todo> *db;

  DeleteTodo(vector<Todo> *db) : db(db) {}

  Outcome middlewares() {
    return MiddleWares<DeleteTodo>()
        .add(new Router<DeleteTodo>(HTTP_DELETE_METHOD, {"/todos/<id>"}))
        .outcome(*this);
  }

  Response response() {
    if (!is_integer(uri_args["id"])) {
      throw HTTP_STATUS_NO_CONTENT;
    }

    int id = convert_to_integer(uri_args["id"]);

    try {
      db->erase(db->begin() + id);
    } catch (...) {
    }
    return status(HTTP_STATUS_NO_CONTENT);
  }
};

#endif
