#include "test.h"
#include "db_base.h"
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

void test_time() {
  {
    Time time;
    fstream file;
    file.open("test.txt", fstream::out | fstream::binary);
    time >> file;
    std::cout << "read  time:" << setbase(16) << time.change_time << '\n';
    file.close();
  }
  {
    Time time;
    fstream file;
    file.open("test.txt", fstream::in | fstream::binary);
    time << file;
    std::cout << "write time: " << setbase(16) << time.change_time << '\n';
    file.close();
  }
}

void test_directory() {
  Directory dir;
  path_buffer = "/home/moon/Desktop";
  fstream file;
  file.open("test.txt", fstream::out | fstream::binary);
  dir >> file;
  file.close();
  file.open("test.txt", fstream::in | fstream::binary);
  dir << file;
  std::cout << "path: " << dir.full_path << '\n';
  std::cout << "time: " << setbase(16) << dir.change_time.change_time << '\n';
}

void test_filename() {
  {
    File filename;
    filename.filename = "environment.sh";
    fstream file;
    file.open("test.txt", fstream::out | fstream::binary);
    std::cout << "writing filename: " << filename.filename << '\n';
    filename >> file;
  }
  {
    File filename;
    fstream file;
    file.open("test.txt", fstream::in | fstream::binary);
    filename << file;
    std::cout << "reading filaname: " << filename.filename << '\n';
  }
}
