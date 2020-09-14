// A Fizz Buzz example which makes use of the fact that routes are persistant
// between requests.

#include "../src/firestorm.h"

class FizzBuzz : public Route {
private:
  int n;

public:
  // We don't define a middleware to use the default of Outcome::Success so
  // this route is used for all requests.

  Response response() {
    // Fizz Buzz
    n++;

    if (n % 3 == 0 && n % 5 == 0) {
      return plain("FizzBuzz");
    }
    if (n % 3 == 0) {
      return plain("Fizz");
    }
    if (n % 5 == 0) {
      return plain("Buzz");
    }

    return plain(std::to_string(n));
  }
};

int main() {
  FireStorm().add_route(new FizzBuzz()).ignite();
}
