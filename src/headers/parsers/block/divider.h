//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_BLOCK_DIVIDER_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_BLOCK_DIVIDER_H_

#include "parsers/abstract.h"

class BlockDividerParser : public AbstractParser {
public:
  BlockDividerParser() = delete;
  explicit BlockDividerParser(AbstractParser *master) {
    this->master = master;
    this->rule = regex(R"(^\-{3,})");
  }
  size_t parseBlock(DOM::Node *parent, const char *input, const size_t size) override {
    cmatch match = cmatch();
    if (!regex_search(input, match, rule)) return 0;
    parent->addChild(new DOM::Node(DOM::HR));
    return match.length();
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_BLOCK_DIVIDER_H_
