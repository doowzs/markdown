//
// Created by Tianyun Zhang on 2020/3/19.
//

#include "dom.h"
#include "common.h"

namespace DOM {

Node::Node(string t, map<string, string> as) : tag(move(t)), attrs(move(as)) {
  next = child = nullptr;
}

} // namespace DOM
