//
// Created by Tianyun Zhang on 2020/3/19.
//

#include "dom.h"
#include "common.h"

namespace DOM {

Node::Node(string content) : content(move(content)) {
  tag = RAW;
  attrs = map<string, string>();
  children = vector<Node *>();
}

Node::Node(enum Tags tag) : tag(tag) {
  attrs = map<string, string>();
  children = vector<Node *>();
}

Node::Node(enum Tags tag, map<string, string> attrs)
    : tag(tag), attrs(move(attrs)) {
  children = vector<Node *>();
}

void Node::addChild(Node *child) { children.emplace_back(child); }

ostream &operator<<(ostream &os, Node &node) {
  if (node.tag == RAW) {
    os << node.content;
    for (auto &child : node.children) {
      os << *child;
    }
  } else {
    os << "<" << node.tag;
    for (auto &attr : node.attrs) {
      os << " " << attr.first << "=\"" << attr.second << "\"";
    }
    os << ">";
    for (auto &child : node.children) {
      os << *child;
    }
    os << "</" << node.tag << ">";
  }
  return os;
}

} // namespace DOM
