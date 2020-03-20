//
// Created by Tianyun Zhang on 2020/3/20.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_INLINE_IMAGE_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_INLINE_IMAGE_H_

#include "parsers/abstract.h"

class InlineImageParser : public AbstractParser {
public:
  InlineImageParser() = delete;
  explicit InlineImageParser(AbstractParser *master) {
    this->master = master;
    this->rule = regex(R"(^\!\[(.*)\]\((.*)\))");
  }
  size_t parseInline(DOM::Node *parent, const char *input, const size_t size) override {
    cmatch match = cmatch();
    if (!regex_search(input, match, rule)) return 0;
    auto image = new DOM::Node(DOM::IMG, {
        {"alt", match[1].str()},
        {"src", match[2].str()},
    });
    parent->addChild(image);
    return match.length();
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_INLINE_IMAGE_H_
