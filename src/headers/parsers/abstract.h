//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_ABSTRACT_PARSER_H_
#define MARKDOWN_SRC_HEADERS_ABSTRACT_PARSER_H_

#include "common.h"
#include "regex.h"
#include "dom.h"

#define regex_search regex_search_line

class AbstractParser {
protected:
  regex rule;
  AbstractParser *master{}; // IoC

public:
  virtual size_t parseBlock(DOM::Node *parent, const char *input, const size_t size) {
    return 0;
  }
  virtual size_t parseInline(DOM::Node *parent, const char *input, const size_t size) {
    return 0;
  }
};

#endif // MARKDOWN_SRC_HEADERS_ABSTRACT_PARSER_H_
