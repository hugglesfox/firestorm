#ifndef TOOD_ROUTE_GET
#define TODO_ROUTE_GET

#include "../../../src/firestorm.h"
#include "../middleware.h"
#include "../models.h"

// A route to get a specific todo
class GetTodo : public Route {
public:
  UriArgs uri_args;
  vector<Todo> *db;

  // Register middlewares
  Outcome middlewares() {
    return MiddleWares<GetTodo>()
        .add(new Router<GetTodo>(HTTP_GET_METHOD, {"/todos/<id>"}))
        .add(new TodoDb<GetTodo>())
        .outcome(*this);
  }

  Response response() {
    if (!is_integer(uri_args["id"])) {
      throw HTTP_STATUS_NOT_FOUND;
    }

    int id = convert_to_integer(uri_args["id"]);

    try {
      return json_data(db->at(id).to_json(), HTTP_STATUS_OK);
    } catch (const std::out_of_range &) {
      throw HTTP_STATUS_NOT_FOUND;
    }
  }
};

#endif
