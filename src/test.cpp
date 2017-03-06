#include "test.h"
#include "db.h"
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

void test_db() {
  {
    QsDB db;
    db.open();
    Entry entry;
    entry.entry_type = Entry::DIRECTORY;
    Directory dir;
    dir.change_time.change_time = 0x1234;
    dir.full_path = "random-path";
    db.writeEntry(entry);
    db.writeDirectory(dir);
    dir.change_time.change_time = 0x4321;
    dir.full_path = "random-forest";
    db.writeEntry(entry);
    db.writeDirectory(dir);
    File file;
    file.filename = "helloworld.txt";
    db.writeFile(file);
  }
  {
    QsDB db;
    db.open();
    Entry entry;
    entry = db.getEntry();
    std::cout << "entry type: " << setbase(16) << (int)entry.entry_type << '\n';
    auto dir = db.getDirectory();
    std::cout << "directory time: " << dir.change_time.change_time << '\n';
    std::cout << "directory path: " << dir.full_path << '\n';
    entry = db.getEntry();
    auto d = db.getDirectory();
    std::cout << "directory time: " << d.change_time.change_time << '\n';
    std::cout << "directory path: " << d.full_path << '\n';
    auto file = db.getFile();
    std::cout << "file          : " << file.filename << '\n';
  }
}
