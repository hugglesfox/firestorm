#ifndef TOOD_ROUTE_CREATE
#define TODO_ROUTE_CREATE

#include "firestorm.h"
#include "../middleware.h"
#include "../models.h"

// A route to update a todo
class UpdateTodo : public Route {
public:
  UriArgs uri_args;
  Todo body;
  vector<Todo> *db;

  UpdateTodo(vector<Todo> *db) : db(db) {}

  // Register middlewares
  Outcome middlewares() {
    return MiddleWares<UpdateTodo>()
        .add(new Router<UpdateTodo>(HTTP_PUT_METHOD, {"/todos/<id>"}))
        .add(new ParseTodo<UpdateTodo>())
        .outcome(*this);
  }

  Response response() {
    if (!is_integer(uri_args["id"])) {
      throw HTTP_STATUS_NOT_FOUND;
    }

    int id = convert_to_integer(uri_args["id"]);

    try {
      Todo *todo = &(db->at(id));

      // Don't allow for duplicate todos
      for (Todo t : *db) {
        if (body == t) {
          throw HTTP_STATUS_CONFLICT;
        }
      }

      todo->text = body.text;
      todo->is_done = body.is_done;

    } catch (const std::out_of_range &) {
      throw HTTP_STATUS_NOT_FOUND;
    }

    // Make the returned JSON look a bit nicer
    json response = create_json();
    json_set_object(response, "todo", body.to_json());

    return json_data(response);
  }
};

#endif
