//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_BLOCK_PARAGRAPH_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_BLOCK_PARAGRAPH_H_

#include "parsers/abstract.h"

class BlockParagraphParser : public AbstractParser {
public:
  BlockParagraphParser() = delete;
  explicit BlockParagraphParser(AbstractParser *master) {
    this->master = master;
  }
  size_t parseBlock(DOM::Node *parent, const char *input, const size_t size) override {
    size_t length = 0;
    string content = string();
    while (*input != '\n') {
      content += *input;
      ++input;
      ++length;
    }
    auto *paragraph = new DOM::Node(DOM::P);
    master->parseInline(paragraph, content.c_str(), length);
    parent->addChild(paragraph);
    return length;
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_BLOCK_PARAGRAPH_H_
