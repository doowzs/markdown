//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_HEADER_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_HEADER_H_

#include "parsers/abstract.h"

class HeaderParser : public AbstractParser {
private:
  regex reg;

public:
  HeaderParser() = delete;
  explicit HeaderParser(AbstractParser *master) {
    this->master = master;
    reg = std::regex(R"(^\s*(#{1,6})\s?(.*))");
  }
  size_t parseBlock(DOM::Node *parent, const char *input, const size_t size) override {
    cmatch match = cmatch();
    if (!regex_search(input, match, reg)) return 0;

    auto header = new DOM::Node(
        (enum DOM::Tags)((int)DOM::H1 + match[1].length() - 1),
        map<string, string>{{"id", match[2].str()}});
    master->parseInline(header, match[2].str().c_str(), match[2].length());
    parent->addChild(header);
    return match.length();
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_HEADER_H_
