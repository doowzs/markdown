//
// Created by Tianyun Zhang on 2020/3/20.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_INLINE_HEADER_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_INLINE_HEADER_H_

#include "parsers/abstract.h"

class InlineHeaderParser : public AbstractParser {
public:
  InlineHeaderParser() = delete;
  explicit InlineHeaderParser(AbstractParser *master) {
    this->master = master;
    this->rule = regex(R"(^\s*(#{1,6})\s?(.*))");
  }
  size_t parseInline(DOM::Node *parent, const char *input, const size_t size) override {
    cmatch match = cmatch();
    if (!regex_search(input, match, rule)) return 0;

    auto header = new DOM::Node(
        (enum DOM::Tags)((int)DOM::H1 + match[1].length() - 1),
        map<string, string>{{"id", match[2].str()}});
    master->parseInline(header, match[2].str().c_str(), match[2].length());
    parent->addChild(header);
    return match.length();
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_INLINE_HEADER_H_
