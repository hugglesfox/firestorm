#include "catch.hpp"
#include "html.h"

TEST_CASE("test html template parsing") {
  string html = "<p>{hello} {animal}</p>";
  HtmlVars vars = {{"animal", "dog"}};

  REQUIRE(parse_html(html, vars) == "<p>{hello} dog</p>");
}

