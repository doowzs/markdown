//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_LINE_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_LINE_H_

#include "common.h"

class LineParser {
private:
  regex strongReg, italicReg, linkReg;

public:
  LineParser() {
    strongReg = regex(R"(\*\*(.*)(\*\*)?)"); // <- non greedy regex
    italicReg = regex(R"(\*(.*)\*)");
    linkReg = regex(R"(\[(.*)\]\((.*)\))");
  }
  DOM::Node *parse(const string &s) {
    cmatch match;
    size_t pos = 0, length = s.length();
    auto *node = new DOM::Node(string());
    while (pos < length) {
      string content;
      while (pos < length) {
        if (s[pos] == '*' or s[pos] == '[') break;
        content += s[pos];
        ++pos;
      }
      node->addChild(new DOM::Node(content));
      string substr = s.substr(pos);
      if (regex_search(substr.c_str(), match, strongReg)) {
        auto strong = new DOM::Node(DOM::STRONG);
        strong->addChild(parse(match[1].str()));
        node->addChild(strong);
        pos += match.length();
      } else if (regex_search(substr.c_str(), match, italicReg)) {
        auto italic = new DOM::Node(DOM::ITALIC);
        italic->addChild(parse(match[1].str()));
        node->addChild(italic);
        pos += match.length();
      } else if (regex_search(substr.c_str(), match, linkReg)) {
        auto hyperlink = new DOM::Node(DOM::A, {
            {"href", match[2].str()},
        });
        hyperlink->addChild(parse(match[1].str()));
        node->addChild(hyperlink);
        pos += match.length();
      }
      // all special matches failed...
      if (s[pos] == '*' or s[pos] == '[') {
        string temp;
        temp += s[pos];
        node->addChild(new DOM::Node(temp));
        ++pos;
      }
    }
    return node;
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_LINE_H_
