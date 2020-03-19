#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Usage: markdown <file>" << endl;
    return -1;
  } else {
    size_t length;
    char *buffer;
    fstream fs(argv[1], ios::in);
    if (!fs.is_open()) {
      cerr << "Error: cannot open file " << argv[1] << " for reading." << endl;
      return -2;
    }
    fs.seekg(0, ios::end);
    length = fs.tellg();
    buffer = new char[length];
    fs.seekg(0, ios::beg);
    fs.read(buffer, length);
    cout << buffer << endl;
  }
}