//
// Created by Tianyun Zhang on 2020/3/20.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_INLINE_HEADER_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_INLINE_HEADER_H_

#include "parsers/abstract.h"

class InlineHeaderParser : public AbstractParser {
private:
  regex reg;

public:
  InlineHeaderParser() {
    reg = regex(R"((#{1,6})\s?(.*))");
  }
  pair<DOM::Node *, size_t> parse(char *text) {
    cmatch match;
    if (!regex_search(text, match, reg)) {
      return make_pair(nullptr, 0);
    }
    return make_pair(nullptr, 0);

  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_INLINE_HEADER_H_
