#pragma once
#include <stdexcept>

using namespace std;

class entry_write_error : public runtime_error {
public:
  entry_write_error() : runtime_error("error in write entry") {}
};

class entry_read_error : public runtime_error {
public:
  entry_read_error() : runtime_error("error in read entry") {}
};

class directory_write_error : public runtime_error {
public:
  directory_write_error() : runtime_error("error in read directory") {}
};

class directory_read_error : public runtime_error {
public:
  directory_read_error() : runtime_error("error in read directory") {}
};

class file_read_error : public runtime_error {
public:
  file_read_error() : runtime_error("error in read file") {}
};
class file_write_error : public runtime_error {
public:
  file_write_error() : runtime_error("error in write file") {}
};
