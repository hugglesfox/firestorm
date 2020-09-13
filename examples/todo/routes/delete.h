#ifndef TOOD_ROUTE_GET
#define TODO_ROUTE_GET

#include "../../../src/firestorm.h"
#include "../middleware.h"
#include "../models.h"

// A route to delete a todo
class DeleteTodo : public Route {
public:
  UriArgs uri_args;
  vector<Todo> *db;

  // Register middlewares
  Outcome middlewares() {
    return MiddleWares<DeleteTodo>()
        .add(new Router<DeleteTodo>(HTTP_DELETE_METHOD, {"/todos/<id>"}))
        .add(new TodoDb<DeleteTodo>())
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
    throw HTTP_STATUS_NO_CONTENT;
  }
};

#endif
