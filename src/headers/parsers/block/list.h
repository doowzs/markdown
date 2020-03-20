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
  size_t parseList(DOM::Node *parent, const char *input, const size_t size, const size_t indent, const bool ordered) {
    auto list = new DOM::Node(ordered ? DOM::OL : DOM::UL);
    cmatch match = cmatch();
    size_t symbol = 0;
    size_t length = 0;
    while (true) {
      while (length < size and iscntrl(input[length])) ++length;
      if (length >= size) break;

      if (regex_search(input + length, match, ordered ? olReg : ulReg)) {
        if (match[1].length() == indent) {
          auto item = new DOM::Node(DOM::LI);
          master->parseInline(item, match[3].str().c_str(), match[3].length());
          list->addChild(item);
          symbol = match[2].length();
          length += match.length();
        } else if (symbol != 0 and match[1].length() == indent + symbol) {
          length += parseList(list, input + length, size - length, indent + symbol, ordered);
        } else {
          break;
        }
      } else {
        if (regex_search(input + length, match, ordered ? ulReg : olReg) and
            (symbol != 0 and match[1].length() == indent + symbol)) {
          length += parseList(list, input + length, size - length, indent + symbol, not ordered);
        } else {
          break;
        }
      }
    }
    parent->addChild(list);
    return length;
  }
  size_t parseBlock(DOM::Node *parent, const char *input, const size_t size) override {
    if (regex_search(input, ulReg)) {
      return parseList(parent, input, size, 0, false);
    } else if (regex_search(input, olReg)) {
      return parseList(parent, input, size, 0, true);
    } else {
      return 0;
    }
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_BLOCK_LIST_H_