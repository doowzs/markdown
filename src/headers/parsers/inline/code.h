//
// Created by Tianyun Zhang on 2020/3/20.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_INLINE_CODE_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_INLINE_CODE_H_

#include "parsers/abstract.h"

class InlineCodeParser : public AbstractParser {
public:
  InlineCodeParser() = delete;
  explicit InlineCodeParser(AbstractParser *parser) {
    this->master = master;
    this->rule = regex(R"(^`(.+?)`)");
  }
  size_t parseInline(DOM::Node *parent, const char *input, const size_t size) override {
    cmatch match = cmatch();
    if (!regex_search(input, match, rule)) return 0;
    auto code = new DOM::Node(DOM::CODE);
    auto content = new DOM::Node(match[1].str()); // raw content
    parent->addChild(code->addChild(content));
    return match.length();
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_INLINE_CODE_H_
