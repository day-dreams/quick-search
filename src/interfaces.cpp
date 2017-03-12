#include "interfaces.h"
#include "db.h"
#include "db_base.h"
#include <boost/filesystem.hpp>
#include <ctime>
#include <exception>
#include <iostream>
#include <list>
#include <stack>
#include <string>

using namespace std;
using namespace boost;

inline bool can_be_read(filesystem::path &p) {
  try {
    auto status = filesystem::status(p).permissions();
    if (status & filesystem::perms::others_read)
      return true;
  } catch (std::exception &e) {
  }
  return false;
}

void qs_init(const char *root) {
  if (!root)
    return;
  QsDB new_db;
  new_db.open();
  Entry file_entry, directory_entry, end_entry;
  file_entry.entry_type = Entry::FILE;
  directory_entry.entry_type = Entry::DIRECTORY;
  end_entry.entry_type = Entry::END;
  stack<filesystem::path> dir_col;
  dir_col.push(filesystem::path(root));
  while (!dir_col.empty()) {
    try {
      auto current_path = dir_col.top();
      dir_col.pop();
      Directory dir;
      dir.change_time.change_time = filesystem::last_write_time(current_path);
      dir.full_path = current_path.string();
      new_db.writeEntry(directory_entry);
      new_db.writeDirectory(dir);
      if (can_be_read(current_path))
        for (auto &sub : filesystem::directory_iterator(current_path)) {
          if (filesystem::is_directory(sub)) { /*目录，进一步判断*/
            if (filesystem::is_symlink(sub)) { /*链接，视为文件，避免重复遍历*/
              File file;
              file.filename = sub.path().filename().string();
              new_db.writeEntry(file_entry);
              new_db.writeFile(file);
            } else { /*目录，延迟处理*/
              dir_col.push(sub.path());
            }
          } else { /*文件，写入db*/
            File file;
            file.filename = sub.path().filename().string();
            new_db.writeEntry(file_entry);
            new_db.writeFile(file);
          }
        }
    } catch (std::exception &e) {
      ;
    }
  }
}

void qs_search(const char *to_search) {
  if (!to_search)
    return;
  string pattern(to_search), current_path;
  list<string> match_result;
  QsDB db;
  db.open();
  bool flag = false;
  while (!db.db_end_reached()) {
    auto entry = db.getEntry();
    if (entry.entry_type == Entry::DIRECTORY) {
      flag = false;
      auto dir = db.getDirectory();
      current_path = dir.full_path;
      if (current_path.find(pattern) != string::npos) {
        match_result.push_back(current_path);
        flag = true;
      }
    } else if (entry.entry_type == Entry::FILE) {
      auto file = db.getFile();
      if (flag | file.filename.find(pattern) != string::npos) {
        match_result.push_back(current_path + "/" + file.filename);
      }
    }
  }
  for (auto &entry : match_result) {
    std::cout << entry << '\n';
  }
}

void qs_update(const char *argv) {
  remove(custom_db_path);
  qs_init(argv);
}
//
// void qs_update(const char *argv) {
//   QsDB old_db, new_db;
//   old_db.open();
//   string temp_path(custom_db_path);
//   auto ite = temp_path.find('/');
//   if (ite != string::npos) {
//     temp_path.insert(ite + 1, 1, '.');
//     // std::cout << "103 temp path: " << temp_path << '\n';
//
//   } else {
//     temp_path.insert(temp_path.begin(), 1, '.');
//     // std::cout << "107 temp path: " << temp_path << '\n';
//   }
//   new_db.open(temp_path);
//   while (!old_db.db_end_reached()) {
//     auto entry = old_db.getEntry();
//   new_entry:
//     if (entry.entry_type == Entry::DIRECTORY) {
//       auto dir = old_db.getDirectory();
//       if (dir.changed()) { /*需要更新*/
//         auto entry = old_db.getEntry();
//
//       } else { /*直接copy*/
//       }
//
//     } else if (entry.entry_type == Entry::FILE) {
//       ;
//     }
//   }
// }
