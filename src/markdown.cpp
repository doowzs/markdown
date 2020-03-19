//
// Created by Tianyun Zhang on 2020/3/19.
//

#include "markdown.h"
#include "parsers/paragraph.h"

namespace Markdown {

DocumentParser::DocumentParser() {
  root = new DOM::Node("body", map<string, string>());
  parsers.emplace_back(new ParagraphParser());
}

}