//
// Created by Tianyun Zhang on 2020/3/19.
//

#ifndef MARKDOWN_SRC_HEADERS_DOM_NODE_H_
#define MARKDOWN_SRC_HEADERS_DOM_NODE_H_

#include "common.h"

namespace DOM {
enum Tags {
  BODY,
  H1 = 1,
  H2 = 2,
  H3 = 3,
  H4 = 4,
  H5 = 5,
  H6 = 6,
  UL,
  OL,
  LI,
  PRE,
  P,
  A,
  CODE,
  STRONG,
  RAW,
};
class Node {
private:
  enum Tags tag;
  string content;
  map<string, string> attrs;
  vector<Node *> children;

public:
  explicit Node(string content);
  explicit Node(enum Tags tag);
  Node(enum Tags tag, map<string, string> attrs);
  void addChild(Node *child);
  friend ostream &operator<<(ostream &os, Node &node);
};
} // namespace DOM

#endif // MARKDOWN_SRC_HEADERS_DOM_NODE_H_
