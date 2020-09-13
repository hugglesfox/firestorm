#include "../../src/firestorm.h"
#include "routes/create.h"
#include "routes/delete.h"
#include "routes/get.h"
#include "routes/list.h"
#include <stdexcept>

// The Todo "database"
vector<Todo> todos;

int main() {
  FireStorm()
      .add_route(new ListTodos())
      .add_route(new GetTodo())
      .add_route(new CreateTodo())
      .add_route(new DeleteTodo())
      .ignite(5000);
  return 0;
}
