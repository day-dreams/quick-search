#include "db_base.h"
#include <ctime>
#include <iostream>

std::string filename_buffer = "default filename";
std::string path_buffer = "default path";

const uint8_t Entry::DIRECTORY = 1;
const uint8_t Entry::FILE = 2;
const uint8_t Entry::END = 3;

Entry::Entry() {}

bool Entry::isDirectory() { return this->entry_type == Entry::DIRECTORY; }
bool Entry::isFile() { return this->entry_type == Entry::FILE; }
bool Entry::isEnd() { return this->entry_type == Entry::END; }

bool Entry::operator>>(std::fstream &file) {
  //  std::cout << "file flag in write entry:" << file.good() << '\n';

  switch (entry_type) {
  case Entry::DIRECTORY:
    file.put('\0' + 1);
    break;
  case Entry::FILE:
    file.put('\0' + 2);
    break;
  case Entry::END:
    file.put('\0' + 3);
    break;
  }
  //  std::cout << "file flag in write entry:" << file.good() << '\n';
  if (file.bad() | !file.is_open() | file.eof())
    return false;
  else
    return true;
}

bool Entry::operator<<(std::fstream &file) {
  if (!file | file.eof())
    return false;
  this->entry_type = file.get();
  return true;
}

Time::Time() { this->change_time = time(nullptr); }

bool Time::operator<<(std::fstream &file) {
  // std::cout << "direcotry flag in read time: " << file.good() << '\n';
  file.read((char *)&this->change_time, 4);
  // std::cout << "direcotry flag in read time: " << file.good() << '\n';
  if (file)
    return true;
  else
    return false;
}

bool Time::operator>>(std::fstream &file) {
  // std::cout << "direcotry flag in write time: " << file.good() << '\n';
  file.write((char *)&this->change_time, 4);
  // std::cout << "direcotry flag in write time: " << file.good() << '\n';

  if (file)
    return true;
  else
    return false;
}

Directory::Directory() { this->change_time.change_time = time(nullptr); }

Directory::Directory(time_t time, std::string &s) : full_path(s) {
  this->change_time.change_time = time;
}

bool Directory::operator>>(std::fstream &file) {
  this->change_time >> file;
  // std::cout << "file flag: " << file.good() << '\n';
  file << full_path;
  file.put(' ');
  // std::cout << "file flag: " << file.good() << '\n';

  if (file)
    return true;
  else
    return false;
}

bool Directory::operator<<(std::fstream &file) {
  // std::cout << "direcotry flag: " << file.good() << '\n';
  this->change_time << file;
  file >> full_path;
  file.get();
  // std::cout << "direcotry flag: " << file.good() << '\n';
  if (file)
    return true;
  else
    return false;
}

bool Directory::change_before(time_t another) {
  if (this->change_time.change_time < another)
    return true;
  else
    return false;
}

File::File() : filename(filename_buffer) {}

bool File::operator<<(std::fstream &file) {
  file >> filename;
  file.get();

  if (file)
    return true;
  else
    return false;
}

bool File::operator>>(std::fstream &file) {
  file << filename;
  file.put(' ');
  if (file)
    return true;
  else
    return false;
}
