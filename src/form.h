#ifndef FIRESTORM_FORM
#define FIRESTORM_FORM

#include "../include/splashkit/splashkit.h"
#include <unordered_map>

#include "headers.h"
#include "middleware.h"
#include "utils.h"

using FormData = std::unordered_map<string, string>;

FormData parse_form(string data);

// A middleware to parse urlencoded forms
template <typename R> class Form : public MiddleWare<R> {
public:
  Outcome outcome(R &route, http_request request) {
    if (headers(request)["Content-Type"] !=
        "application/x-www-form-urlencoded") {
      return Outcome::Failure;
    }

    route.form_data = parse_form(request_body(request));
    return Outcome::Success;
  }
};

#endif
