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

vector<Todo> todos = {};
Todo current_todo;

Outcome parse_todo(http_request request) {
  write_line(request_body(request));
  json body = json_from_string(request_body(request));

  if (json_has_key(body, "text")) {
    current_todo.text = json_read_string(body, "text");
  }

  if (json_has_key(body, "is_done")) {
    current_todo.is_done = json_read_bool(body, "is_done");
  }
  return Outcome::Success;
}

Response list_todos(UriVars _) {
  vector<json> todos_json;
  for (Todo todo : todos) {
    todos_json.push_back(todo.to_json());
  }

  json response = create_json();
  json_set_array(response, "todos", todos_json);

  return json_data(response, HTTP_STATUS_OK);
}

Response get_todo(UriVars vars) {
  if (!is_number(vars["id"])) {
    throw HTTP_STATUS_BAD_REQUEST;
  }

  try {
    int i = convert_to_integer(vars["id"]);
    return json_data(todos.at(i).to_json(), HTTP_STATUS_OK);
  } catch (...) {
    throw HTTP_STATUS_NOT_FOUND;
  }
}

Response create_todo(UriVars _) {
  if (current_todo.text != "") {
    todos.push_back(current_todo);
    return json_data(current_todo.to_json(), HTTP_STATUS_CREATED);
  }

  throw HTTP_STATUS_BAD_REQUEST;
}

Response delete_todo(UriVars vars) {
  if (!is_number(vars["id"])) {
    throw HTTP_STATUS_BAD_REQUEST;
  }

  try {
    int i = convert_to_integer(vars["id"]);
    todos.erase(todos.begin() + i);
    return status(HTTP_STATUS_NO_CONTENT);
  } catch (...) {
    throw HTTP_STATUS_NO_CONTENT;
  }
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
