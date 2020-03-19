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
  HeaderParser() { reg = std::regex(R"(^\s*(#{1,6})(.*))"); }
  pair<DOM::Node *, size_t> parse(char *text) override {
    cmatch match;
    if (!regex_search(text, match, reg)) {
      return make_pair(nullptr, 0);
    }
    auto header = new DOM::Node(
        (enum DOM::Tags)((int)DOM::H1 + match[1].length() - 1),
            map<string, string>{{"id", match[2].str()}});
    lineParser.parse(header, match[2].str());
    return make_pair(header, match.str().size());
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_HEADER_H_
