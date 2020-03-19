//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSER_H_
#define MARKDOWN_SRC_HEADERS_PARSER_H_

#include "common.h"
#include "dom.h"
#include "parsers/abstract.h"

namespace Markdown {
class DocumentParser {
public:
  DOM::Node *root;
  vector<AbstractParser *> parsers;

  DocumentParser();
  void parse(char *text);
};
}

#endif // MARKDOWN_SRC_HEADERS_PARSER_H_
