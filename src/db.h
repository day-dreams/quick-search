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
  QsDB();
  QsDB(const QsDB &d) = delete;
  QsDB operator=(const QsDB &d) = delete;

  /*判断数据库文件是否读取完毕*/
  bool db_end_reached();

  /*打开数据库文件，默认路径为现有数据库*/
  bool open(std::string db_path = custom_db_path);

  /*初始化新数据库,写入magic number*/
  bool init_new_db();

  /*获取+写入entry*/
  Entry getEntry();
  bool writeEntry(Entry &entry);

  /*获取+写入directory*/
  Directory getDirectory();
  bool writeDirectory(Directory &direcotry);

  /*获取+写入file*/
  File getFile();
  bool writeFile(File &file);
};
