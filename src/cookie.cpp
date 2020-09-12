#include "cookie.h"

// Construct a Set-Cookie header
string Cookie::construct() {
  string cookie = "Set-Cookie: ";
  cookie += name;
  cookie += "=";
  cookie += value;

  if (max_age > 0) {
    cookie += "; " + std::to_string(max_age);
  }

  if (secure) {
    cookie += "; Secure";
  }

  if (http_only) {
    cookie += "; HttpOnly";
  }

  switch (same_site) {
  case Strict:
    cookie += "; SameSite=Strict";
    break;
  case Lax:
    cookie += "; SameSite=Lax";
    break;
  case None:
    cookie += "; SameSite=None";
    break;
  }

  return cookie;
}
