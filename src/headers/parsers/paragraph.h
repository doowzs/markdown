//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_PARAGRAPH_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_PARAGRAPH_H_

#include "regex.h"
#include "parsers/abstract.h"

class ParagraphParser : public AbstractParser {
private:
  regex reg;
public:
  ParagraphParser() {
    reg = regex(".*$");
  }
  pair<DOM::Node *, size_t> parse(char *text) override {
    cmatch match;
    if (regex_search(text, match, reg)) {
      auto *node = new DOM::Node("p", map<string, string>());
      // TODO: Parse line text
      auto *content = new DOM::Node(match.str());
      node->addChild(content);
      return make_pair(node, match.str().size());
    } else {
      return make_pair(nullptr, 0);
    }
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_PARAGRAPH_H_
