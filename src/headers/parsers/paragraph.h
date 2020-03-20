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
  ParagraphParser() = delete;
  explicit ParagraphParser(AbstractParser *master) {
    this->master = master;
    reg = regex(R"(^.*)");
  }
  size_t parseBlock(DOM::Node *parent, const char *input, const size_t size) override {
    cmatch match = cmatch();
    if (!regex_search(input, match, reg)) return 0;
    auto *node = new DOM::Node(DOM::P);
    master->parseInline(node, match.str().c_str(), match.length());
    parent->addChild(node);
    return match.length();
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_PARAGRAPH_H_
