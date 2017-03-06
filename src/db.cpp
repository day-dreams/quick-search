#include "db.h"
#include "config.h"
#include "exceptions.h"
#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>

using namespace boost;
using namespace std;

QsDB::QsDB() {}

bool QsDB::open(std::string db_path) {
  this->db_path = db_path;
  filesystem::path db(db_path);
  if (filesystem::exists(db)) /*读取现有数据库*/ {
    db_file.open(db_path, fstream::binary | fstream::in);
    uint32_t magic;
    db_file.read((char *)&magic, 4);
    if (magic != MAGIC_NUMBER)
      return false;
  } else /*新建数据库*/
  {
    db_file.open(db_path, fstream::binary | fstream::out);
    init_new_db();
  }
  if (db_file)
    return true;
  else
    return false;
}

bool QsDB::init_new_db() {
  std::cout << "sizeof mn: " << sizeof(MAGIC_NUMBER) << '\n';
  db_file.write((char *)&MAGIC_NUMBER, sizeof(MAGIC_NUMBER));
  if (db_file && db_file.is_open())
    return true;
  else
    return false;
}

Entry QsDB::getEntry() {
  Entry entry;
  if (entry << db_file)
    return entry;
  else
    throw entry_read_error();
}

bool QsDB::writeEntry(Entry &entry) { return (entry >> db_file); }

Directory QsDB::getDirectory() {
  Directory dir;
  if (dir << db_file)
    return dir;
  else
    throw directory_read_error();
}

bool QsDB::writeDirectory(Directory &directory) { return directory >> db_file; }

File QsDB::getFile() {
  File file;
  if (file << db_file)
    return file;
  else
    throw file_read_error();
}

bool QsDB::writeFile(File &file) { return file >> db_file; }
