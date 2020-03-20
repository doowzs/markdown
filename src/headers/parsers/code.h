//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_CODE_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_CODE_H_

#include "parsers/abstract.h"

class CodeParser : public AbstractParser {
private:
  regex reg;

public:
  explicit CodeParser(AbstractParser *master) {
    this->master = master;
    reg = regex(R"(^```(.*)\n?)");
  }
  size_t parseBlock(DOM::Node *parent, const char *input, const size_t size) override {
    cmatch match;
    if (!regex_search(input, match, reg)) return 0;

    string lang = match[1].str().empty() ? "plaintext" : match[1].str();
    auto *node = new DOM::Node(DOM::PRE, map<string, string>{{"lang", lang}});
    int length = match.length();
    string code;
    while (input[length] != '\0') {
      if (regex_search(input + length, reg)) {
        break;
      }
      code += DOM::escape(input[length]);
      ++length;
    }
    auto *hljs = new DOM::Node(DOM::CODE, map<string, string>{{"class", lang}}, code);
    node->addChild(hljs);
    parent->addChild(node);
    return length + 3;
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_CODE_H_
