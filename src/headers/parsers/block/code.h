//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_BLOCK_CODE_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_BLOCK_CODE_H_

#include "parsers/abstract.h"

class BlockCodeParser : public AbstractParser {
public:
  BlockCodeParser() = delete;
  explicit BlockCodeParser(AbstractParser *master) {
    this->master = master;
    this->rule = regex(R"(^\s*```(.*)\n?)");
  }
  size_t parseBlock(DOM::Node *parent, const char *input, const size_t size) override {
    cmatch match;
    if (!regex_search(input, match, rule)) return 0;

    string lang = match[1].str().empty() ? "plaintext" : match[1].str();
    auto *node = new DOM::Node(DOM::PRE, map<string, string>{{"lang", lang}});
    size_t length = match.length();
    string code;
    while (length < size) {
      if (input[length] == '`' and regex_search(input + length, rule)) break;
      code += DOM::escape(input[length]);
      ++length;
    }
    auto *hljs = new DOM::Node(DOM::CODE, map<string, string>{{"class", lang}}, code);
    node->addChild(hljs);
    parent->addChild(node);
    return min(length + 3, size); // avoid overflow
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_BLOCK_CODE_H_
