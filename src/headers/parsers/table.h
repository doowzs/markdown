//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSERS_TABLE_H_
#define MARKDOWN_SRC_HEADERS_PARSERS_TABLE_H_

#include "parsers/abstract.h"

class TableParser : public AbstractParser {
private:
  regex reg;

public:
  TableParser() {
    reg = regex(R"(\|(.*)\|)"); // greedy regex
  }
  pair<DOM::Node *, size_t> parseTable(char *text) {
    int row = 0, column = 0;
    size_t length = 1;
    cmatch match;

    regex_search(text, match, reg);
    column = match.length();
    for (auto &c : match.str()) {
      if (c != '|') --column;
    }

    regex colReg = regex(R"((.*?)\|)"); // non-greedy regex
    regex rowReg = regex(string(R"(((.*?)\|){)") + to_string(column) + string(R"(})"));

    auto table = new DOM::Node(DOM::TABLE, map<string, string> {
        {"class", "table"},
    });
    auto thead = new DOM::Node(DOM::THEAD);
    auto theadRow = new DOM::Node(DOM::TR);
    for (int i = 0; i < column; ++i) {
      regex_search(text + length, match, colReg);
      auto theadCell = new DOM::Node(DOM::TH, map<string, string> {
          {"scope", "col"},
      });
      theadRow->addChild(lineParser.parse(theadCell, match[1].str()));
      length += match.length();
    }
    thead->addChild(theadRow);
    table->addChild(thead);

    auto tbody = new DOM::Node(DOM::TBODY);
    while (true) {
      while (text[length] != '\0' and iscntrl(text[length])) {
        ++length;
      }
      if (!regex_search(text + length, match, rowReg)) break;
      ++length;
      auto trow = new DOM::Node(DOM::TR);
      for (int i = 0; i < column; ++i) {
        regex_search(text + length, match, colReg);
        auto trowCell = new DOM::Node(DOM::TD);
        trow->addChild(lineParser.parse(trowCell, match[1].str()));
        length += match.length();
      }
      if (row == 0) {
        delete trow; // ignore the alignment row
      } else {
        tbody->addChild(trow);
      }
      ++row;
    }
    --row;
    table->addChild(tbody);

    return make_pair(table, length);
  }
  pair<DOM::Node *, size_t> parse(char *text) override {
    if (!regex_search(text, reg)) {
      return make_pair(nullptr, 0);
    }
    return parseTable(text);
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_TABLE_H_
