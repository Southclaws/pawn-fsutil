#include "impl.hpp"
#include "common.hpp"

std::map<int, fs::directory_iterator> openDirPool;
int openDirPoolCount = 0;

bool Impl::Exists(std::string path)
{
    return fs::exists(path);
}

int Impl::CreateDir(std::string path)
{
    int ret = 0;

    try {
        ret = fs::create_directories(path);
    } catch (std::exception e) {
        logprintf("create_directories failed: %s", e.what());
        ret = -1;
    }

    return ret;
}

int Impl::RemoveDir(std::string path, bool recursive)
{
    int ret;
    std::error_code ec;

    if (recursive) {
        ret = (int)fs::remove_all(path, ec);
    } else {
        ret = (int)fs::remove(path, ec);
    }
    if (ec) {
        // negative values indicate error
        return -ec.value();
    }
    return ret;
}

int Impl::OpenDir(std::string path)
{
    fs::directory_iterator iter = fs::directory_iterator(path);
    openDirPool[openDirPoolCount] = iter;
    return openDirPoolCount++;
}

bool Impl::DirNext(int id, std::string& entry, fs::file_type& type)
{
    auto val = openDirPool.find(id);
    if (val == openDirPool.end()) {
        return false;
    }

    // todo: store entry, increment iterator

    return true;
}

int Impl::CloseDir(int id)
{
    openDirPool.erase(id);
    return 0;
}

int Impl::MoveFile(std::string from, std::string to)
{
    return rename(from.c_str(), to.c_str());
}

int Impl::CopyFile(std::string from, std::string to)
{
    try {
        fs::copy(from, to);
    } catch (std::exception e) {
        return 1;
    }

    return 0;
}
