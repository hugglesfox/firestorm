#ifndef TOOD_ROUTE_GET
#define TODO_ROUTE_GET

#include "firestorm.h"
#include "../middleware.h"
#include "../models.h"

// A route to get a specific todo
class GetTodo : public Route {
public:
  UriArgs uri_args;
  vector<Todo> *db;

  GetTodo(vector<Todo> *db) : db(db) {}

  Outcome middlewares() {
    return MiddleWares<GetTodo>()
        .add(new Router<GetTodo>(HTTP_GET_METHOD, {"/todos/<id>"}))
        .outcome(*this);
  }

  Response response() {
    if (!is_integer(uri_args["id"])) {
      throw HTTP_STATUS_NOT_FOUND;
    }

    int id = convert_to_integer(uri_args["id"]);

    try {
      // Make the returned JSON look a bit nicer
      json response = create_json();
      json_set_object(response, "todo", db->at(id).to_json());

      return json_data(response);
    } catch (const std::out_of_range &) {
      throw HTTP_STATUS_NOT_FOUND;
    }
  }
};

#endif
