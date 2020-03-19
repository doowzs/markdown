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
  HeaderParser() { reg = std::regex("^\\s*(#{1,6}) (.*)"); }
  pair<DOM::Node *, size_t> parse(char *text) override {
    cmatch match;
    if (regex_search(text, match, reg)) {
      auto *node = new DOM::Node("h" + to_string(match[1].str().length()),
                                 map<string, string>{{"id", match[2].str()}});
      // TODO: parse line text
      auto *content = new DOM::Node(match[2].str());
      node->addChild(content);
      return make_pair(node, match.str().size());
    } else {
      return make_pair(nullptr, 0);
    }
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_HEADER_H_
