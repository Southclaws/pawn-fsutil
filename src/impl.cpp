// implementation

#if defined(_WIN32)
// windows file functions
#include "dirent.h"
#include <direct.h>
#include <io.h>
#else
// linux file functions
#include <dirent.h>
#include <unistd.h>
#endif

#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

#include <amx/amx.h>

#include "impl.hpp"

bool Impl::Exists(string path)
{
#if defined(_WIN32)
    return access(path.c_str(), 0);
#else
    struct stat st;
    return stat(path.c_str(), &st);
#endif
}

int CreateDir(string path)
{
#if defined(_WIN32)
    return mkdir(path.c_str());
#else
    return mkdir(path.c_str(), 0755);
#endif

    return 0;
}

int RemoveDir(string path, bool recursive)
{
    // todo: recursive
    return rmdir(path);
}

int MoveFile(string from, string to)
{
    return rename(from.c_str(), to.c_str();
}

int CopyFile(string from, string to)
{
    if (!(fopen(from.c_str(), "r"))) {
        return 1;
    }

    std::ifstream fromStream(from, std::fstream::binary);
    std::ofstream toStream(to, std::fstream::trunc | std::fstream::binary);

    toStream << fromStream.rdbuf();

    fromStream.close();
    toStream.close();

    return 0;
}