#pragma once

#include <cstdint>
#include <fstream>

/*
  索引表结构：
    magic_number
+   entry
+   .....

*/

/*两个缓冲取，在每个directory/file被读取时使用，
  避免空间浪费*/
extern std::string filename_buffer;
extern std::string path_buffer;

/*数据entry*/
class Entry {
public:
  static const uint8_t DIRECTORY;
  static const uint8_t FILE;
  static const uint8_t END;

  uint8_t entry_type = 0;

  Entry();
  // Entry(const Entry &) = delete;
  // Entry &operator=(const Entry &) = delete;

  /*类型判断*/
  bool isDirectory();
  bool isFile();
  bool isEnd();

  /*从文件中读取*/
  bool operator<<(std::fstream &file);
  /*写入到文件中*/
  bool operator>>(std::fstream &file);
};

/*时间类型,time()返回值*/
class Time {
public:
  uint32_t change_time = 0;

  Time();
  // Time(const Time &t) = delete;
  // Time &operator=(const Time &t) = delete;
  //
  /*从文件中读取*/
  bool operator<<(std::fstream &file);
  /*写入到文件中*/
  bool operator>>(std::fstream &file);
};

/*目录类型，在文件中表现为：时间+绝对路径字符串*/
class Directory {
public:
  Time change_time;
  std::string &full_path = path_buffer;

  Directory();
  Directory(time_t time, std::string &s);
  // Directory(const Directory &d) = delete;
  // Directory operator=(const Directory &d) = delete;

  /*写入到文件*/
  bool operator>>(std::fstream &file);
  /*从文件中读取*/
  bool operator<<(std::fstream &file);
  /*比较时间先后*/
  bool changed();
};

/*文件类型，在文件中表现为：文件名字符串*/
class File {
public:
  std::string &filename;

  File();
  // File(const File &f) = delete;
  // File operator=(const File &f) = delete;

  /*写入到文件*/
  bool operator>>(std::fstream &file);
  /*从文件中读取*/
  bool operator<<(std::fstream &file);
};
