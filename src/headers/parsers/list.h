//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_LIST_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_LIST_H_

#include "parsers/abstract.h"

class ListParser : public AbstractParser {
private:
  regex ulReg, olReg;

public:
  ListParser() {
    ulReg = regex(R"(^(\s*)([\+\-\*] )(.*))");
    olReg = regex(R"(^(\s*)(\d+\. )(.*))");
  }
  pair<DOM::Node *, size_t> parseList(char *text, size_t indent, bool ordered) {
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
          auto item = new DOM::Node(DOM::LI);
          auto subList = parseList(text, match[1].length(), not ordered);
          item->addChild(subList.first);
          list->addChild(item);
          text += subList.second;
          length += subList.second;
        } else {
          break;
        }
      } else {
        if (match[1].length() == indent) {
          auto item = new DOM::Node(DOM::LI);
          item->addChild(lineParser.parse(match[3].str()));
          list->addChild(item);
          symbol = match[2].length();
          text += match.length();
          length += match.length();
        } else if (symbol != 0 and match[1].length() == indent + symbol) {
          auto subList = parseList(text, match[1].length(), ordered);
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
  pair<DOM::Node *, size_t> parse(char *text) override {
    if (regex_search(text, ulReg)) {
      return parseList(text, 0, false);
    } else if (regex_search(text, olReg)) {
      return parseList(text, 0, true);
    } else {
      return make_pair(nullptr, 0);
    }
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_LIST_H_
