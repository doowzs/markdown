//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_ABSTRACT_PARSER_H_
#define MARKDOWN_SRC_HEADERS_ABSTRACT_PARSER_H_

#include "common.h"
#include "dom.h"
#include "parsers/line.h"

class AbstractParser {
protected:
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
