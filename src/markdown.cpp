//
// Created by Tianyun Zhang on 2020/3/19.
//

#include "markdown.h"
#include "parsers/block/code.h"
#include "parsers/block/divider.h"
#include "parsers/block/header.h"
#include "parsers/block/list.h"
#include "parsers/block/paragraph.h"
#include "parsers/block/table.h"
#include "parsers/inline/code.h"
#include "parsers/inline/header.h"
#include "parsers/inline/hyperlink.h"
#include "parsers/inline/image.h"
#include "parsers/inline/italic.h"
#include "parsers/inline/plain.h"
#include "parsers/inline/strike.h"
#include "parsers/inline/strong-italic.h"
#include "parsers/inline/strong.h"

namespace Markdown {

DocumentParser::DocumentParser() {
  blockParsers.emplace_back(new BlockHeaderParser(this));
  blockParsers.emplace_back(new BlockDividerParser(this));
  blockParsers.emplace_back(new BlockCodeParser(this));
  blockParsers.emplace_back(new BlockListParser(this));
  blockParsers.emplace_back(new BlockTableParser(this));
  blockParsers.emplace_back(new BlockParagraphParser(this));

  inlineParsers.emplace_back(new InlineHeaderParser(this));
  inlineParsers.emplace_back(new InlineCodeParser(this));
  inlineParsers.emplace_back(new InlineImageParser(this));
  inlineParsers.emplace_back(new InlineHyperlinkParser(this));
  inlineParsers.emplace_back(new InlineStrikeParser(this));
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