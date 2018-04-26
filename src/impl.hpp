#ifndef FSUTIL_IMPL_H
#define FSUTIL_IMPL_H

#if defined WIN32
#include <filesystem>
namespace fs = std::experimental::filesystem::v1;
#else
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#endif

#include <fstream>
#include <iostream>
#include <map>
#include <string>

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
};

#endif
