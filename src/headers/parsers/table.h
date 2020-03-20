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
  explicit TableParser(AbstractParser *master) {
    this->master = master;
    reg = regex(R"(\|(.*)\|)"); // greedy regex
  }
  pair<DOM::Node *, size_t> parseTable(const char *text, const size_t size) {
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
      master->parseInline(theadCell, match[1].str().c_str(), match[1].length());
      theadRow->addChild(theadCell);
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
        master->parseInline(trowCell, match[1].str().c_str(), match[1].length());
        trow->addChild(trowCell);
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
  size_t parseBlock(DOM::Node *parent, const char *input, const size_t size) override {
    if (!regex_search(input, reg)) return 0;
    auto res = parseTable(input, size);
    parent->addChild(res.first);
    return res.second;
  }
};

#endif // MARKDOWN_SRC_HEADERS_PARSERS_TABLE_H_
