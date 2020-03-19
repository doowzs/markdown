//
// Created by Tianyun Zhang on 2020/3/19.
//

#include "dom.h"
#include "common.h"

namespace DOM {

Node::Node(string tag, map<string, string> attrs)
    : raw(false), tag(move(tag)), attrs(move(attrs)) {
  children = vector<Node *>();
}

Node::Node(string content) : raw(true), content(move(content)) {
  tag = string();
  attrs = map<string, string>();
  children = vector<Node *>();
}

void Node::addChild(Node *child) { children.emplace_back(child); }

ostream &operator<<(ostream &os, Node &node) {
  if (node.raw) {
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
