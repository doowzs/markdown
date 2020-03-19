//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_LIST_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_LIST_H_

#include "parsers/abstract.h"

class ListParser : public AbstractParser {
private:
  regex ulReg, olReg;

public:
  ListParser() {
    ulReg = regex(R"(^(\s*)(\+|-|\* )(.*))");
    olReg = regex(R"(^(\s*)(\d+\. )(.*))");
  }
  pair<DOM::Node *, size_t> parseList(char *text, size_t indent, bool ordered) {
    auto node = new DOM::Node(ordered ? DOM::OL : DOM::UL);
    cmatch match;
    size_t length = 0;
    while (true) {
      if (!regex_search(text, match, ordered ? olReg : ulReg)) {
        break;
      } else {
        if (match[0].length() < indent) {
          break;
        } else if (match[0].length() == indent) {
          auto child = new DOM::Node(DOM::LI);
        }
      }
    }
    return make_pair(node, length);
  }
  pair<DOM::Node *, size_t> parse(char *text) override {
    if (regex_search(text, ulReg)) {
      return parseList(text, 0, false);
    } else if (regex_search(text, olReg)) {
      return parseList(text, 0, true);
    } else {
      return make_pair(nullptr, 0);
    }
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_LIST_H_
