//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_LINE_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_LINE_H_

#include "common.h"

class LineParser {
private:
  regex headerReg, strongItalicReg, strongReg, italicReg, imageReg, linkReg, codeReg;

public:
  LineParser() {
    // use non-greedy regex to handle cases like "**A***B*"
    headerReg = regex(R"((#{1,6})\s?(.*))");
    strongItalicReg = regex(R"(^\*\*\*(.+?)\*\*\*)");
    strongReg = regex(R"(^\*\*(.+?)\*\*)");
    italicReg = regex(R"(^\*(.+?)\*)");
    imageReg = regex(R"(^\!\[(.*)\]\((.*)\))");
    linkReg = regex(R"(^\[(.*)\]\((.*)\))");
    codeReg = regex(R"(^`(.+?)`)");
  }
  void parse(DOM::Node *node, const string &s) {
    cmatch match;
    size_t pos = 0, length = s.length();
    while (pos < length) {
      string content;
      while (pos < length) {
        if (s[pos] == '#' or s[pos] == '*' or s[pos] == '!' or
            s[pos] == '[' or s[pos] == '`') break;
        content += DOM::escape(s[pos]);
        ++pos;
      }
      if (!content.empty()) node->addChild(new DOM::Node(content));
      if (pos >= length) {
        break;
      } else {
        string substr = s.substr(pos);
        if (regex_search(substr.c_str(), match, headerReg)) {
          auto header = new DOM::Node((enum DOM::Tags)((int)DOM::H1 + match[1].length() - 1));
          parse(header, match[2].str());
          node->addChild(header);
          pos += match.length();
        } else if (regex_search(substr.c_str(), match, strongItalicReg)) {
          auto strong = new DOM::Node(DOM::STRONG);
          auto italic = new DOM::Node(DOM::ITALIC);
          parse(italic, match[1].str());
          node->addChild(strong->addChild(italic));
          pos += match.length();
        } else if (regex_search(substr.c_str(), match, strongReg)) {
          auto strong = new DOM::Node(DOM::STRONG);
          parse(strong, match[1].str());
          node->addChild(strong);
          pos += match.length();
        } else if (regex_search(substr.c_str(), match, italicReg)) {
          auto italic = new DOM::Node(DOM::ITALIC);
          parse(italic, match[1].str());
          node->addChild(italic);
          pos += match.length();
        } else if (regex_search(substr.c_str(), match, imageReg)) {
          auto image = new DOM::Node(DOM::IMG, {
              {"alt", match[1].str()},
              {"src", match[2].str()},
          });
          node->addChild(image);
          pos += match.length();
        } else if (regex_search(substr.c_str(), match, linkReg)) {
          auto hyperlink = new DOM::Node(DOM::A, {
              {"href", match[2].str()},
          });
          parse(hyperlink, match[1].str());
          node->addChild(hyperlink);
          pos += match.length();
        } else if (regex_search(substr.c_str(), match, codeReg)) {
          auto code = new DOM::Node(DOM::CODE);
          node->addChild(code->addChild(new DOM::Node(match[1].str())));
          pos += match.length();
        } else { // all regex match failed...
          string temp;
          temp += DOM::escape(s[pos]);
          node->addChild(new DOM::Node(temp));
          ++pos;
        }
      }
    }
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_LINE_H_
