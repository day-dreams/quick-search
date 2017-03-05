#include "test.h"
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
  test_time();
  test_directory();
  test_filename();
  return 0;
}
