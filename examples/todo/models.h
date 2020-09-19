#ifndef TODO_MODELS
#define TODO_MODELS

#include "firestorm.h"

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

#endif
