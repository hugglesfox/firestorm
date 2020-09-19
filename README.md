
<p align="center">
  <img height="600" src="https://github.com/hugglesfox/firestorm/blob/master/firestorm.png" alt="FireStorm" title="FireStorm">
</p>

FireStorm aims to be a simple yet flexible web frame work which is built on top of [SplashKit’s](https://www.splashkit.io) networking features. FireStorm provides abstractions for routing, middlewares, cookies, redirects and more.

**Note:** FireStorm currently relies on features from the develop branch of skm.

```cpp
#include "firestorm.h"

// Create the route Hello
class Hello : public Route {
public:
  // uri_args is a hashmap of strings containing variable identifiers and their
  // corresponding values
  UriArgs uri_args;

  // Register middlewares to process requests
  Outcome middlewares() {
    return MiddleWares<Hello>()
        // Add the built in Router middleware to route get requests on the
        // paths /hello and /hello/<name>?<age>
        .add(new Router<Hello>(HTTP_GET_METHOD,
                               {"/hello", "/hello/<name>?<age>"}))
        .outcome(*this);
  }

  // Create a response to return to the client
  Response response() {
    return plain("Hello " + uri_args["name"] + " aged " + uri_args["age"]);
  }
};

int main() {
  // Register the Hello route and run the web server
  FireStorm().add_route(new Hello()).ignite();
  return 0;
}
```

For a more complete example, see [examples/todo/](https://github.com/hugglesfox/firestorm/tree/master/examples/todo)

## Features

### Pluggable middlewares

- All interactions with raw http requests are managed with middlewares.
- Middlewares are pluggable therefore are enabled an a route to route basis.
  - If a middleware fails then the request isn't handled by that route.
- Various built in middlewares are available for routing and form parsing.
  - The built in router middleware allows for variable path and argument handling.
  - Yes that does mean you do not have to use the built in router if you wish.

### Simple request and response handling

- Simple abstractions to handle redirects as well as serving of plain text, JSON and HTML.
- Abstractions for parsing and creating cookies.
- Request header parsing.
- Custom error pages.

### Built on SplashKit

- Allows you to easily utilise the abstractions provided by [SplashKit](https://www.splashkit.io).
- Native support for the `json` and `http_request` types as well as SplashKit resources.

## Building

FireStorm uses the Meson build system.

### Initial Setup

Set up the Meson environment.

```
$ meson build
```

#### Enabling Examples

By default the examples won't be compiled. Set the `build_examples` build option to `true` to compile examples.

```
$ meson configure -Dbuild_examples=true
```

### Compiling

Compile using a Meson backend (here we're using Ninja).

```
$ cd build
$ ninja
```

## Documentation

Documentation can be found [here](https://github.com/hugglesfox/firestorm/wiki).

## Licencing

FireStorm is licenced under the MIT licence.
