#ifndef TOOD_ROUTE_LIST
#define TODO_ROUTE_LIST

#include "../../../src/firestorm.h"
#include "../middleware.h"
#include "../models.h"

// A route to list all the todos
class ListTodos : public Route {
public:
  UriArgs uri_args;
  vector<Todo> *db;

  ListTodos(vector<Todo> *db) : db(db) {}

  Outcome middlewares() {
    return MiddleWares<ListTodos>()
        .add(new Router<ListTodos>(HTTP_GET_METHOD, {"/todos"}))
        .outcome(*this);
  }

  Response response() {
    vector<json> json_todos;
    for (Todo todo : *db) {
      json_todos.push_back(todo.to_json());
    }

    // Make the returned JSON look a bit nicer
    json response = create_json();
    json_set_array(response, "todos", json_todos);
    return json_data(response);
  }
};

#endif
