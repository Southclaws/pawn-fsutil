#include "impl.hpp"

bool Impl::Exists(std::string path)
{
    return fs::exists(path);
}

int Impl::CreateDir(std::string path)
{
    if (fs::create_directories(path)) {
        return 0;
    } else {
        return 1;
    }
}

int Impl::RemoveDir(std::string path, bool recursive)
{
    std::error_code ec;
    int ret = fs::remove_all(path, ec);
    if (ec) {
        // negative values indicate error
        return -ec.value();
    }
    return ret;
}

int Impl::ListDir(std::string path, std::vector<std::string>& result)
{
    for (auto& entry : fs::directory_iterator(path)) {
        result.push_back(entry.path);
    }

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