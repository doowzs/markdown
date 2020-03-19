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
  CodeParser() { reg = regex(R"(^```(.*)\n?)"); }
  pair<DOM::Node *, size_t> parse(char *text) override {
    cmatch match;
    if (!regex_search(text, match, reg)) {
      return make_pair(nullptr, 0);
    }
    string lang = match[1].str().empty() ? "plaintext" : match[1].str();
    auto *node = new DOM::Node(DOM::PRE, map<string, string>{{"lang", lang}});
    int length = match.length();
    string code;
    while (text[length] != '\0') {
      if (regex_search(text + length, reg)) {
        break;
      }
      code += text[length];
      ++length;
    }
    auto *hljs = new DOM::Node(DOM::CODE, map<string, string>{{"class", lang}}, code);
    node->addChild(hljs);
    return make_pair(node, length + 3);
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_CODE_H_
