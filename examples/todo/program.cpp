#include "../../src/firestorm.h"
#include "models.h"
#include "routes/create.h"
#include "routes/delete.h"
#include "routes/get.h"
#include "routes/list.h"
#include "routes/update.h"

int main() {
  // The Todo "database"
  vector<Todo> db;

  FireStorm()
      .add_route(new ListTodos(&db))
      .add_route(new GetTodo(&db))
      .add_route(new CreateTodo(&db))
      .add_route(new DeleteTodo(&db))
      .add_route(new UpdateTodo(&db))
      .ignite(5000);
  return 0;
}
