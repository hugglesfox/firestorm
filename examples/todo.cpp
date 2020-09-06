#include "../firestorm.h"
#include "../include/splashkit/splashkit.h"

struct Todo {
  string text;
  bool is_done;

  json to_json() {
    json todo = create_json();
    json_set_string(todo, "text", text);
    json_set_bool(todo, "is_done", is_done);
    return todo;
  }
};

// To do database
vector<Todo> todos = {};

// Gets updated on each request depending on the data sent.
// This might not always be a valid todo.
Todo current_todo;

// Middleware to attempt to parse the current todo from a request
Outcome parse_todo(http_request request) {
  // This is gonna be annoying and log warnings unless it's a post request.
  json body = json_from_string(request_body(request));

  // Update current_todo
  if (json_has_key(body, "text")) {
    current_todo.text = json_read_string(body, "text");
  }

  if (json_has_key(body, "is_done")) {
    current_todo.is_done = json_read_bool(body, "is_done");
  }

  return Outcome::Success;
}

// A GET route for /todos to list all the todos
Response list_todos(UriVars _) {
  vector<json> todos_json;
  for (Todo todo : todos) {
    todos_json.push_back(todo.to_json());
  }

  json response = create_json();
  json_set_array(response, "todos", todos_json);

  return json_data(response, HTTP_STATUS_OK);
}

// A GET route for /todos/<id> to list a single todo
Response get_todo(UriVars vars) {
  if (!is_number(vars["id"])) {
    throw HTTP_STATUS_BAD_REQUEST;
  }

  int i = convert_to_integer(vars["id"]);

  try {
    return json_data(todos.at(i).to_json(), HTTP_STATUS_OK);
  } catch (...) {
    throw HTTP_STATUS_NOT_FOUND;
  }
}

// A POST route for /todos to create a new todo
Response create_todo(UriVars _) {
  if (current_todo.text != "") {
    todos.push_back(current_todo);
    return json_data(current_todo.to_json(), HTTP_STATUS_CREATED);
  }

  throw HTTP_STATUS_BAD_REQUEST;
}

// A DELETE route for /todos/<id> to delete a todo
Response delete_todo(UriVars vars) {
  if (!is_number(vars["id"])) {
    throw HTTP_STATUS_BAD_REQUEST;
  }

  int i = convert_to_integer(vars["id"]);

  try {
    todos.erase(todos.begin() + i);
  } catch (...) {
  }

  // Return 203 no matter whether it failed or not as if the todo your trying to
  // delete already doesn't exist then it was still a successful deletion.
  return status(HTTP_STATUS_NO_CONTENT);
}

int main() {
  FireStorm()
      .get("/todos", list_todos)
      .get("/todos/<id>", get_todo)
      .post("/todos", create_todo)
      .del("/todos/<id>", delete_todo)
      .middleware(parse_todo)
      .ignite(5000);
}
