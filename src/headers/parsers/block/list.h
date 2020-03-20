//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_BLOCK_LIST_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_BLOCK_LIST_H_

#include "parsers/abstract.h"

class BlockListParser : public AbstractParser {
private:
  regex ulReg, olReg;

public:
  BlockListParser() = delete;
  explicit BlockListParser(AbstractParser *master) {
    this->master = master;
    ulReg = regex(R"(^(\s*)([\+\-\*] )(.*))");
    olReg = regex(R"(^(\s*)(\d+\. )(.*))");
  }
  pair<DOM::Node *, size_t> parseList(DOM::Node *parent, const char *text, const size_t size, const size_t indent, const bool ordered) {
    auto list = new DOM::Node(ordered ? DOM::OL : DOM::UL);
    cmatch match;
    size_t symbol = 0;
    size_t length = 0;
    while (true) {
      while (*text != '\0' and iscntrl(*text)) {
        ++text;
        ++length;
      }
      if (!regex_search(text, match, ordered ? olReg : ulReg)) {
        if (regex_search(text, match, ordered ? ulReg : olReg) and
            (symbol != 0 and match[1].length() == indent + symbol)) {
          auto subList = parseList(list, text, match[1].length(), indent + 1, !ordered);
          list->addChild(subList.first);
          text += subList.second;
          length += subList.second;
        } else {
          break;
        }
      } else {
        if (match[1].length() == indent) {
          auto item = new DOM::Node(DOM::LI);
          master->parseInline(item, match[3].str().c_str(), match[3].length());
          list->addChild(item);
          symbol = match[2].length();
          text += match.length();
          length += match.length();
        } else if (symbol != 0 and match[1].length() == indent + symbol) {
          auto subList = parseList(list, text, match[1].length(), indent + 1, ordered);
          list->addChild(subList.first);
          text += subList.second;
          length += subList.second;
        } else {
          break;
        }
      }
    }
    return make_pair(list, length);
  }
  size_t parseBlock(DOM::Node *parent, const char *input, const size_t size) override {
    if (regex_search(input, ulReg)) {
      auto res = parseList(parent, input, size, 0, false);
      parent->addChild(res.first);
      return res.second;
    } else if (regex_search(input, olReg)) {
      auto res = parseList(parent, input, size, 0, true);
      parent->addChild(res.first);
      return res.second;
    } else {
      return 0;
    }
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_BLOCK_LIST_H_
