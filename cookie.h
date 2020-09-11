#ifndef FIRESTORM_COOKIE
#define FIRESTORM_COOKIE

#include "include/splashkit/splashkit.h"

enum SameSiteOption {
  Strict,
  Lax,
  None,
};

struct Cookie {
  string name;
  string value;
  unsigned int max_age = 0;
  bool secure = false;
  bool http_only = false;
  SameSiteOption same_site = SameSiteOption::Lax;

  string construct();
  Cookie(string name, string value) : name(name), value(value) {}
};

#endif
