//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_HEADER_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_HEADER_H_

#include "parsers/abstract.h"

class HeaderParser : public AbstractParser {
private:
  regex reg;

public:
  HeaderParser() { reg = std::regex(R"(^\s*(#{1,6}.*))"); }
  pair<DOM::Node *, size_t> parse(char *text) override {
    cmatch match;
    if (!regex_search(text, match, reg)) {
      return make_pair(nullptr, 0);
    }
    return make_pair(lineParser.parse(match[1].str()), match.str().size());
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_HEADER_H_
