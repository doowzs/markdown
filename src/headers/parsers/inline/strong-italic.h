//
// Created by Tianyun Zhang on 2020/3/20.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_INLINE_STRONG_ITALIC_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_INLINE_STRONG_ITALIC_H_

#include "parsers/abstract.h"

class InlineStrongItalicParser : public AbstractParser {
public:
  InlineStrongItalicParser() = delete;
  explicit InlineStrongItalicParser(AbstractParser *master) {
    this->master = master;
    this->rule = regex(R"(^\*\*\*(.+?)\*\*\*)", regex::optimize); // non-greedy regex
  }
  size_t parseInline(DOM::Node *parent, const char *input, const size_t size) override {
    cmatch match = cmatch();
    if (!regex_search(input, match, rule)) return 0;
    auto strong = new DOM::Node(DOM::STRONG);
    auto italic = new DOM::Node(DOM::ITALIC);
    master->parseInline(italic, match[1].str().c_str(), match[1].length());
    parent->addChild(strong->addChild(italic));
    return match.length();
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_INLINE_STRONG_ITALIC_H_
