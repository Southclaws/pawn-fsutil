#ifndef FSUTIL_IMPL_H
#define FSUTIL_IMPL_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
namespace fs = std::experimental::filesystem::v1;

#include <amx/amx.h>

namespace Impl {
bool Exists(std::string path);

int CreateDir(std::string path);
int RemoveDir(std::string path, bool recursive);
int ListDir(std::string path, std::vector<std::string>& result);

int MoveFile(std::string from, std::string to);
int CopyFile(std::string from, std::string to);
};

#endif
