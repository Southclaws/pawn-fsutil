#ifndef FSUTIL_IMPL_H
#define FSUTIL_IMPL_H

#include <string>

using std::string;

namespace Impl {
bool Exists(string path);

int CreateDir(string path);
int RemoveDir(string path, bool recursive);
int ListDir(string path, string result[]);

int MoveFile(string from, string to);
int CopyFile(string from, string to);
};

#endif
