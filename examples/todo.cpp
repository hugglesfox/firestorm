#include "../firestorm.h"
#include "../include/splashkit/splashkit.h"
#include <stdexcept>

class Todo {
public:
  string text;
  bool is_done;

  bool operator==(Todo other) { return text == other.text; }

  json to_json() {
    json todo = create_json();
    json_set_string(todo, "text", text);
    json_set_bool(todo, "is_done", is_done);
    return todo;
  }
};

// The Todo "database"
vector<Todo> todos;

// A middleware to create a connection to the database
template <typename R> class TodoDb : public MiddleWare<R> {
public:
  Outcome handle(R &route, http_request _) {
    route.db = &todos;
    return Outcome::Success;
  }
};

// A middlware to authorize users using a http header
template <typename R> class Authenticate : public MiddleWare<R> {
public:
  Outcome handle(R &_, http_request request) {
    if (headers(request)["Authorization"] == "Bearer auth_token") {
      return Outcome::Success;
    }
    throw HTTP_STATUS_UNAUTHORIZED;
  }
};

// A middleware to parse Todo objects from json request bodies
template <typename R> class ParseTodo : public MiddleWare<R> {
public:
  Outcome handle(R &route, http_request request) {
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

// A route to list all the todos
class ListTodos : public Route {
public:
  UriArgs uri_args;
  vector<Todo> *db;

  Outcome middlewares() {
    return MiddleWares<ListTodos>()
        .add(new Router<ListTodos>(HTTP_GET_METHOD, {"/todos"}))
        .add(new TodoDb<ListTodos>())
        .outcome(*this);
  }

  // Register middlewares
  Response route() {
    vector<json> json_todos;
    for (Todo todo : *db) {
      json_todos.push_back(todo.to_json());
    }

    json response = create_json();
    json_set_array(response, "todos", json_todos);
    return json_data(response, HTTP_STATUS_OK);
  }
};

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

  Response route() {
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
        .add(new Authenticate<CreateTodo>())
        .add(new ParseTodo<CreateTodo>())
        .add(new TodoDb<CreateTodo>())
        .outcome(*this);
  }

  Response route() {
    for (Todo todo : *db) {
      if (todo == body) {
        throw HTTP_STATUS_FORBIDDEN;
      }
    }
    todos.push_back(body);
    return json_data(body.to_json(), HTTP_STATUS_CREATED);
  }
};

// A route to delete a todo
class DeleteTodo : public Route {
public:
  UriArgs uri_args;
  vector<Todo> *db;

  // Register middlewares
  Outcome middlewares() {
    return MiddleWares<DeleteTodo>()
        .add(new Router<DeleteTodo>(HTTP_DELETE_METHOD, {"/todos/<id>"}))
        .add(new Authenticate<DeleteTodo>())
        .add(new TodoDb<DeleteTodo>())
        .outcome(*this);
  }

  Response route() {
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

int main() {
  FireStorm()
      .add_route(new ListTodos())
      .add_route(new GetTodo())
      .add_route(new CreateTodo())
      .add_route(new DeleteTodo())
      .ignite(5000);
  return 0;
}
