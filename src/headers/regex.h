//
// Created by Tianyun Zhang on 2020/3/21.
//

#ifndef MARKDOWN_SRC_HEADERS_REGEX_H_
#define MARKDOWN_SRC_HEADERS_REGEX_H_

#include "common.h"

inline size_t get_line_length(const char *input) {
  for (auto *pos = input; true; ++pos) {
    if (*pos == '\0' or *pos == '\n') return pos - input;
  }
}

inline bool regex_search_line(const char *input, regex &rule) {
  return regex_search(input, input + get_line_length(input), rule);
}

inline bool regex_search_line(const char *input, cmatch &match, regex &rule) {
  return regex_search(input, input + get_line_length(input), match, rule);
}

#endif // MARKDOWN_SRC_HEADERS_REGEX_H_
