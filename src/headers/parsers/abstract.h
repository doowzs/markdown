//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_ABSTRACT_PARSER_H_
#define MARKDOWN_SRC_HEADERS_ABSTRACT_PARSER_H_

#include "dom.h"

class AbstractParser {
public:
  virtual pair<DOM::Node *, size_t> parse(char *text) {
    return make_pair(nullptr, 0);
  }
};

#endif // MARKDOWN_SRC_HEADERS_ABSTRACT_PARSER_H_
