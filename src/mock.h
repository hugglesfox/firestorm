#ifndef FIRESTORM_MOCK
#define FIRESTORM_MOCK

#include "firestorm.h"

class MockFireStorm : FireStorm {
public:
  Response ignite(http_request request) {
    return route(request);
  }
};

#endif
