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
        ret = static_cast<int>(fs::remove_all(path, ec));
    } else {
        ret = static_cast<int>(fs::remove(path, ec));
    }
    if (ec) {
        // negative values indicate error
        ret = -ec.value();
    }
    return ret;
}

int Impl::OpenDir(std::string path)
{
    try {
        fs::directory_iterator iter = fs::directory_iterator(path);
        openDirPool[openDirPoolCount] = iter;
        return openDirPoolCount++;
    } catch (std::exception& e) {
        logprintf("directory_iterator failed: %s", e.what());
        return -1;
    }
}

bool Impl::DirNext(int id, std::string& entry, fs::file_type& type)
{
    if (openDirPool.find(id) == openDirPool.end()) {
        return false;
    }

    fs::directory_iterator iter = openDirPool[id];
    fs::directory_iterator end;
    if (iter == end) {
        return false;
    }

    entry = iter->path().string();
    type = iter->status().type();

    iter++;
    openDirPool[id] = iter;

    return true;
}

int Impl::CloseDir(int id)
{
    auto val = openDirPool.find(id);
    if (val == openDirPool.end()) {
        return 1;
    }

    openDirPool.erase(id);
    return 0;
}

int Impl::MoveFile(std::string from, std::string to)
{
    std::error_code ec;
    fs::rename(from, to, ec);
    return ec.value();
}

int Impl::CopyFile(std::string from, std::string to)
{
    std::error_code ec;
    fs::copy(from, to, ec);
    return ec.value();
}

std::string Impl::PathJoin(std::string a, std::string b)
{
    fs::path result(a);
    result.append(b);
    return result.string();
}

std::string Impl::PathBase(std::string input)
{
    fs::path p(input);
    return p.filename().string();
}

std::string Impl::PathDir(std::string input)
{
    fs::path p(input);
    if (p.has_parent_path()) {
		return p.parent_path().make_preferred().string();
    }
    return ".";
}

std::string Impl::PathExt(std::string input)
{
    fs::path p(input);
    if (p.has_extension()) {
        return p.extension().string();
    }
    return "";
}
