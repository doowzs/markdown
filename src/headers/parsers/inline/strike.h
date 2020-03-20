//
// Created by Tianyun Zhang on 2020/3/21.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_INLINE_STRIKE_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_INLINE_STRIKE_H_

#include "parsers/abstract.h"

class InlineStrikeParser : public AbstractParser {
public:
  InlineStrikeParser() = delete;
  explicit InlineStrikeParser(AbstractParser *master) {
    this->master = master;
    this->rule = regex(R"(^~~(.*?)~~)");
  }
  size_t parseInline(DOM::Node *parent, const char *input, const size_t size) override {
    cmatch match = cmatch();
    if (!regex_search(input, match, rule)) return 0;
    auto strike = new DOM::Node(DOM::STRIKE);
    master->parseInline(strike, match[1].str().c_str(), match[1].length());
    parent->addChild(strike);
    return match.length();
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_INLINE_STRIKE_H_
