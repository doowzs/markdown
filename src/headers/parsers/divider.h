//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_DIVIDER_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_DIVIDER_H_

#include "parsers/abstract.h"

class DividerParser : public AbstractParser {
private:
  regex reg;

public:
  DividerParser() {
    reg = regex(R"(^\-{3,})");
  }
  pair<DOM::Node *, size_t> parse(char *text) override {
    cmatch match;
    if (!regex_search(text, match, reg)) {
      return make_pair(nullptr, 0);
    }
    return make_pair(new DOM::Node("<hr/>"), match.length());
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_DIVIDER_H_
