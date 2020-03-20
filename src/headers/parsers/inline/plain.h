//
// Created by Tianyun Zhang on 2020/3/20.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_INLINE_PLAIN_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_INLINE_PLAIN_H_

#include "parsers/abstract.h"

class InlinePlainParser : public AbstractParser {
public:
  InlinePlainParser() = delete;
  explicit InlinePlainParser(AbstractParser *master) {
    this->master = master;
    this->rule = regex(R"(^[^#\*\!\[`]+)"); // avoid #, *, !, [, `
  }
  size_t parseInline(DOM::Node *parent, const char *input, const size_t size) override {
    cmatch match = cmatch();
    if (regex_search(input, match, rule)) {
      parent->addChild(new DOM::Node(match.str()));
      return match.length();
    } else {
      /* Fall-back safe rule: eat one character from input */
      parent->addChild(new DOM::Node(string(1, *input)));
      return 1;
    }
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_INLINE_PLAIN_H_
