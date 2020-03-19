//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_DOM_NODE_H_
#define MARKDOWN_SRC_HEADERS_DOM_NODE_H_

#include "common.h"

namespace DOM {
class Node {
private:
  bool raw;
  string tag;
  string content;
  map<string, string> attrs;
  vector<Node *> children;

public:
  explicit Node(string content);
  Node(string tag, map<string, string> attrs);
  void addChild(Node *child);
  friend ostream &operator<<(ostream &os, Node &node);
};
}

#endif // MARKDOWN_SRC_HEADERS_DOM_NODE_H_
