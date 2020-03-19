//
// Created by Tianyun Zhang on 2020/3/19.
//

#include "markdown.h"
#include "parsers/header.h"
#include "parsers/list.h"
#include "parsers/paragraph.h"

namespace Markdown {

DocumentParser::DocumentParser() {
  root = new DOM::Node(DOM::BODY);
  parsers.emplace_back(new HeaderParser());
  parsers.emplace_back(new ListParser());
  parsers.emplace_back(new ParagraphParser());
}

void DocumentParser::parse(char *text) {
  int pos = 0, len = strlen(text);
  while (pos < len) {
    while (pos < len and isspace(text[pos]))
      ++pos;
    if (pos == len)
      break;
    int last = pos;
    cerr << "Parsed at " << last << "." << endl;
    for (auto &p : parsers) {
      auto res = p->parse(text + pos);
      if (res.first != nullptr) {
        root->addChild(res.first);
        pos += res.second;
        break;
      }
    }
    if (pos == last) {
      cerr << "Parsing failed." << endl;
      break;
    }
  }
}

} // namespace Markdown