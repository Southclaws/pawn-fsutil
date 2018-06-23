#ifndef FSUTIL_IMPL_H
#define FSUTIL_IMPL_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

#include <amx/amx.h>

namespace Impl {
enum ENTRY_TYPE {
    ENTRY_TYPE_DIRECTORY,
    ENTRY_TYPE_FILE
};

bool Exists(std::string path);

int CreateDir(std::string path);
int RemoveDir(std::string path, bool recursive);
int OpenDir(std::string path);
bool DirNext(int id, std::string& entry, fs::file_type& type);
int CloseDir(int id);

int MoveFile(std::string from, std::string to);
int CopyFile(std::string from, std::string to);

std::string PathJoin(std::string a, std::string b);
std::string PathBase(std::string input);
std::string PathDir(std::string input);
std::string PathExt(std::string input);
};

#endif
