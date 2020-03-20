//
// Created by Tianyun Zhang on 2020/3/19.
//

#include "markdown.h"
#include "parsers/code.h"
#include "parsers/divider.h"
#include "parsers/header.h"
#include "parsers/list.h"
#include "parsers/paragraph.h"
#include "parsers/table.h"
#include "parsers/inline/header.h"
#include "parsers/inline/plain.h"
#include "parsers/inline/hyperlink.h"
#include "parsers/inline/strong-italic.h"
#include "parsers/inline/strong.h"
#include "parsers/inline/italic.h"

namespace Markdown {

DocumentParser::DocumentParser() {
  blockParsers.emplace_back(new HeaderParser(this));
  blockParsers.emplace_back(new DividerParser(this));
  blockParsers.emplace_back(new ListParser(this));
  blockParsers.emplace_back(new CodeParser(this));
  blockParsers.emplace_back(new TableParser(this));
  blockParsers.emplace_back(new ParagraphParser(this));

  inlineParsers.emplace_back(new InlineHeaderParser(this));
  inlineParsers.emplace_back(new InlineHyperlinkParser(this));
  inlineParsers.emplace_back(new InlineStrongItalicParser(this));
  inlineParsers.emplace_back(new InlineStrongParser(this));
  inlineParsers.emplace_back(new InlineItalicParser(this));
  inlineParsers.emplace_back(new InlinePlainParser(this));
}

DocumentParser::~DocumentParser() {
  for (auto &p : inlineParsers) delete p;
  for (auto &p : blockParsers) delete p;
}

DOM::Node *DocumentParser::parse(char *input) {
  auto *root = new DOM::Node(DOM::MAIN);
  parseBlock(root, input, strlen(input));
  return root;
}

size_t DocumentParser::parseBlock(DOM::Node *parent, const char *input, const size_t size) {
  size_t pos = 0;
  while (pos < size) {
    while (pos < size and iscntrl(input[pos])) ++pos;
    if (pos >= size) break;

    bool proceeded = false;
    for (auto &p : blockParsers) {
      size_t delta = p->parseBlock(parent, input + pos, size - pos);
      if (delta > 0) {
        pos += delta;
        proceeded = true;
        break;
      }
    }
    assert(proceeded); // avoid infinite loop
  }
  return size;
}

size_t DocumentParser::parseInline(DOM::Node *parent, const char *input, const size_t size) {
  size_t pos = 0;
  while (pos < size) {
    while (pos < size and iscntrl(input[pos])) ++pos;
    if (pos >= size) break;

    bool proceeded = false;
    for (auto &p : inlineParsers) {
      size_t delta = p->parseInline(parent, input + pos, size - pos);
      if (delta > 0) {
        pos += delta;
        proceeded = true;
        break;
      }
    }
    assert(proceeded); // avoid infinite loop
  }
  return size;
}

} // namespace Markdown