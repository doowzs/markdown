//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_DOM_NODE_H_
#define MARKDOWN_SRC_HEADERS_DOM_NODE_H_

#include "common.h"

namespace DOM {
class Node {
public:
  string tag;
  map<string, string> attrs;
  Node *child, *next;

  Node(string t, map<string, string> as);
};
}

#endif // MARKDOWN_SRC_HEADERS_DOM_NODE_H_
