#include "interfaces.h"
//#include "test.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    std::cout << "非法输入" << '\n';
    return -1;
  }
  string option(argv[1]);
  if (option == "-update") {
    if (argc < 3)
      qs_update("~/");
    else
      qs_update(argv[2]);
  } else {
    qs_search(argv[1]);
  }
  return 0;
}
