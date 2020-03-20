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
  }
  size_t parseInline(DOM::Node *parent, const char *input, const size_t size) override {
    parent->addChild(new DOM::Node(string(input)));
    return size;
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_INLINE_PLAIN_H_
