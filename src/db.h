#pragma once
#include "config.h"
#include "db_base.h"
#include <fstream>
#include <string>

class QsDB {
private:
  std::string db_path;
  std::fstream db_file;

public:
  /*构造函数，必须设定数据库路径;
    默认路径则表明是读旧数据，设定路径则表明更新数据*/
  QsDB(std::string db_path = custom_db_path);

  /*获取+写入entry*/
  Entry getEntry();
  bool writeEntry(const Entry &entry);

  /*获取+写入directory*/
  Directory getDirectory();
  bool writeDirectory(const Directory &direcotry);

  /*获取+写入file*/
  File getFile();
  bool writeFile(const File &file);
};
