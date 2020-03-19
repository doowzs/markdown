//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_ABSTRACT_PARSER_H_
#define MARKDOWN_SRC_HEADERS_ABSTRACT_PARSER_H_

class DomNode;

class AbstractParser {
public:
  virtual DomNode *parse(char *text) {
    return nullptr;
  }
};

#endif // MARKDOWN_SRC_HEADERS_ABSTRACT_PARSER_H_
