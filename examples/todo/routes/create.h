#ifndef TOOD_ROUTE_GET
#define TODO_ROUTE_GET

#include "../../../src/firestorm.h"
#include "../middleware.h"
#include "../models.h"

// A route to create a new todo
class CreateTodo : public Route {
public:
  UriArgs uri_args;
  Todo body;
  vector<Todo> *db;

  // Register middlewares
  Outcome middlewares() {
    return MiddleWares<CreateTodo>()
        .add(new Router<CreateTodo>(HTTP_POST_METHOD, {"/todos"}))
        .add(new ParseTodo<CreateTodo>())
        .add(new TodoDb<CreateTodo>())
        .outcome(*this);
  }

  Response response() {
    for (Todo todo : *db) {
      if (todo == body) {
        throw HTTP_STATUS_FORBIDDEN;
      }
    }
    todos.push_back(body);
    return json_data(body.to_json(), HTTP_STATUS_CREATED);
  }
};

#endif
