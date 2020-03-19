//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_PARAGRAPH_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_PARAGRAPH_H_

#include "parsers/abstract.h"

class ParagraphParser : public AbstractParser {
private:
  regex reg;

public:
  ParagraphParser() { reg = regex(R"(^.*)"); }
  pair<DOM::Node *, size_t> parse(char *text) override {
    cmatch match;
    if (!regex_search(text, match, reg)) {
      return make_pair(nullptr, 0);
    }
    auto *node = new DOM::Node(DOM::P);
    lineParser.parse(node, match.str());
    return make_pair(node, match.str().size());
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_PARAGRAPH_H_
