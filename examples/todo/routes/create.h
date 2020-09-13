#ifndef TOOD_ROUTE_CREATE
#define TODO_ROUTE_CREATE

#include "../../../src/firestorm.h"
#include "../middleware.h"
#include "../models.h"

// A route to create a new todo
class CreateTodo : public Route {
public:
  UriArgs uri_args;
  Todo body;
  vector<Todo> *db;

  CreateTodo(vector<Todo> *db) : db(db) {}

  // Register middlewares
  Outcome middlewares() {
    return MiddleWares<CreateTodo>()
        .add(new Router<CreateTodo>(HTTP_POST_METHOD, {"/todos"}))
        .add(new ParseTodo<CreateTodo>())
        .outcome(*this);
  }

  Response response() {
    for (Todo todo : *db) {
      if (todo == body) {
        throw HTTP_STATUS_CONFLICT;
      }
    }
    db->push_back(body);
    return json_data(body.to_json(), HTTP_STATUS_CREATED);
  }
};

#endif
