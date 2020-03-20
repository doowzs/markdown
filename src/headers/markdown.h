//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_PARSER_H_
#define MARKDOWN_SRC_HEADERS_PARSER_H_

#include "common.h"
#include "dom.h"
#include "parsers/abstract.h"

namespace Markdown {
class DocumentParser : public AbstractParser {
public:
  vector<AbstractParser *> blockParsers;
  vector<AbstractParser *> inlineParsers;

  DocumentParser();
  ~DocumentParser();
  DOM::Node *parse(char *text);
  size_t parseBlock(DOM::Node *parent, const char *input, size_t size) override;
  size_t parseInline(DOM::Node *parent, const char *input, size_t size) override;
};
}

#endif // MARKDOWN_SRC_HEADERS_PARSER_H_
