#include "firestorm.h"

string name;

class HelloForm : public Route {
public:
  UriArgs uri_args;
  FormData form_data;

  Outcome middlewares() {
    return MiddleWares<HelloForm>()
        .add(new Router<HelloForm>(HTTP_POST_METHOD, {"/"}))
        .add(new Form<HelloForm>())
        .outcome(*this);
  }

  Response response() {
    name = form_data["name"];
    return redirect("/");
  }
};

class Hello : public Route {
public:
  UriArgs uri_args;

  Outcome middlewares() {
    return MiddleWares<Hello>()
        .add(new Router<Hello>(HTTP_GET_METHOD, {"/"}))
        .outcome(*this);
  }

  Response response() {
    return html("index.html", {{"name", name}});
  }
};

int main() {
  FireStorm()
      .add_route(new Hello())
      .add_route(new HelloForm())
      .ignite();
  return 0;
}
