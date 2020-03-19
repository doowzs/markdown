//
// Created by Tianyun Zhang on 2020/3/19.
//

#include "dom.h"
#include "common.h"

namespace DOM {

const string HTMLHeader = R"(<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>Markdown HTML</title>
    <link href="https://cdn.bootcss.com/github-markdown-css/4.0.0/github-markdown.min.css" rel="stylesheet">
    <link href="https://cdn.bootcss.com/highlight.js/9.15.10/styles/default.min.css" rel="stylesheet">
    <link href="https://cdn.bootcss.com/KaTeX/0.11.1/katex.min.css" rel="stylesheet">
    <style scoped>
        @media not print {
            #container {
                margin: 5rem 10rem;
            }
        }
    </style>
</head>
<body>
    <div id="container">)";

const string HTMLFooter = R"(
    </div>
    <script src="https://cdn.bootcss.com/highlight.js/9.18.1/highlight.min.js"></script>
    <script src="https://cdn.bootcss.com/KaTeX/0.11.1/katex.min.js"></script>
    <script src="https://cdn.bootcss.com/KaTeX/0.11.1/contrib/auto-render.min.js"></script>
    <script>
        hljs.initHighlightingOnLoad();
        renderMathInElement(document.body, {
            delimiters: [
                { left: "$$", right: "$$", display: true },
                { left: "$", right: "$", display: false },
            ]
        });
    </script>
</body>
</html>)";

const map<enum Tags, string> TagStrings{
    {BODY, "body"},   {MAIN, "main"},   {H1, "h1"},       {H2, "h2"},
    {H3, "h3"},       {H4, "h4"},       {H5, "h5"},       {H6, "h6"},
    {UL, "ul"},       {OL, "ol"},       {LI, "li"},       {PRE, "pre"},
    {TABLE, "table"}, {THEAD, "thead"}, {TBODY, "tbody"}, {TR, "tr"},
    {TH, "th"},       {TD, "td"},       {P, "p"},         {A, "a"},
    {IMG, "img"},     {CODE, "code"},   {SPAN, "span"},   {STRONG, "strong"},
    {ITALIC, "i"},    {RAW, "raw"},
};

Node::Node(string content) : content(move(content)) {
  tag = RAW;
  attrs = map<string, string>();
  children = vector<Node *>();
}

Node::Node(enum Tags tag) : tag(tag) {
  if (tag == MAIN) {
    indent = 2; // <body><div><main>...
  }
  attrs = map<string, string>();
  children = vector<Node *>();
}

Node::Node(enum Tags tag, map<string, string> attrs)
    : tag(tag), attrs(move(attrs)) {
  children = vector<Node *>();
}

Node::Node(enum Tags tag, map<string, string> attrs, string content)
    : tag(tag), attrs(move(attrs)), content(move(content)) {
  children = vector<Node *>();
}

Node::~Node() {
  for (auto &c : children) {
    delete c;
  }
}

bool Node::empty() const {
  return tag == RAW and content.empty();
}

Node *Node::addChild(Node *child) {
  // non-leave nodes shall not have content
  assert(content.empty());
  children.emplace_back(child);
  return this;
}

ostream &operator<<(ostream &os, Node &node) {
  if (node.tag == RAW) {
    os << endl;
    for (int i = 0; i < node.indent; ++i) os << "    ";
    if (node.content.empty()) {
      os << "<!--EMPTY-->";
    } else {
      os << node.content;
    }
    for (auto &child : node.children) {
      child->indent = node.indent + (node.empty() ? 0 : 1);
      os << *child;
    }
  } else {
    /* Indent of current DOM node */
    os << endl;
    for (int i = 0; i < node.indent; ++i) os << "    ";
    /* Tag of current DOM node */
    os << "<" << TagStrings.at(node.tag);
    for (auto &attr : node.attrs) {
      os << " " << attr.first << "=\"" << attr.second << "\"";
    }
    os << ">";
    if (node.content.empty()) {
      /* Recursively print all children */
      for (auto &child : node.children) {
        child->indent = node.indent + 1;
        os << *child;
      }
      os << endl;
      for (int i = 0; i < node.indent; ++i) os << "    ";
    } else {
      os << node.content;
    }
    /* Close-tag of current DOM Node */
    os << "</" << TagStrings.at(node.tag) << ">";
  }
  return os;
}

} // namespace DOM
