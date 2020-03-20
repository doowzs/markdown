#include "common.h"
#include "dom.h"
#include "markdown.h"

char *readFromConsole();
char *readFromFile(string &filename);
void parseMarkdown(ostream &os, char *buffer);

int main(int argc, char *argv[]) {
  char *buffer = nullptr;
  fstream fs = fstream();
  string input = string();
  string output = "output.html";

  try {
    if (argc == 1) {
      buffer = readFromConsole();
    } else {
      for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-o")) {
          ++i;
          if (i == argc) {
            throw runtime_error("No output file specified but -o is given.");
          }
          output = argv[i];
        } else {
          input = argv[i];
        }
      }
      if (input.empty()) {
        throw runtime_error("No input file is given.");
      }
      buffer = readFromFile(input);
    }

    fs.open(output, ios::out | ios::trunc);
    if (!fs.is_open()) {
      cerr << "Error: cannot open file output.html for writing." << endl;
    }
    parseMarkdown(fs, buffer);
    fs.close();

    delete []buffer;
  } catch (runtime_error &e) {
    cerr << e.what() << endl;
    return -1;
  }

  return 0;
}

char *readFromConsole() {
  char ch = 0;
  size_t length = 0;
  char *buffer = nullptr;
  string input = string();
  while (!cin.read(&ch, 1).eof()) {
    input += ch;
    ++length;
  }

  fstream fs = fstream("input.md", ios::out | ios::trunc);
  if (!fs.is_open()) {
    throw runtime_error("Cannot open input.md for writing.");
  }
  fs << input;
  fs.close();

  buffer = new char[length];
  memcpy(buffer, input.c_str(), length);
  return buffer;
}

char *readFromFile(string &filename) {
  size_t length = 0;
  char *buffer = nullptr;
  fstream fs = fstream(filename, ios::in | ios::ate);
  if (!fs.is_open()) {
    throw runtime_error("Error: cannot open file \"" + filename +
                        "\" for reading.");
  }
  length = fs.tellg();
  buffer = new char[length];
  fs.seekg(0, ios::beg);
  fs.read(buffer, length);
  fs.close();
  return buffer;
}

void parseMarkdown(ostream &os, char *buffer) {
  auto *parser = new Markdown::DocumentParser;
  auto *root = parser->parse(buffer);
  os << DOM::HTMLHeader << *root << DOM::HTMLFooter;
  delete root;
  delete parser;
}
