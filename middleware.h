#ifndef FIRESTORM_MIDDLEWARE
#define FIRESTORM_MIDDLEWARE

#include "include/splashkit/splashkit.h"

#include "error.h"
#include "routing.h"

class Outcome {
public:
  enum Value {
    Success,
    Failure,
  };

  constexpr Outcome(Value v) : value(v) {}
  operator Value() const { return value; }

  // Compare 2 outcomes and return Success if both are Success
  // I borrowed the idea from Rust's Result.and()
  constexpr Outcome and_success(Outcome other) const {
    if (*this == Outcome::Failure || other == Outcome::Failure) {
      return Outcome::Failure;
    }
    return Outcome::Success;
  };

  // Prevent if(Outcome)
  explicit operator bool() = delete;

  constexpr bool is_success() const { return *this == Outcome::Success; }


private:
  Value value;
};

using MiddleWareFn = Outcome (*)(http_request request);

struct MiddleWare {
  MiddleWareFn handler;
  ErrorFn failure;
};

#endif
