#include <filesystem>
#include <iostream>
#include <map>
#include <string>

#include <amx/amx2.h>

#include "EFileType.hpp"
#include "natives.hpp"
#include "common.hpp"

/// @brief File type lookup
static const std::map<std::filesystem::file_type, FileSystem::EFileType> fileTypeLookup =
{
    { std::filesystem::file_type::none,         FileSystem::EFileType::None },
    { std::filesystem::file_type::not_found,    FileSystem::EFileType::NotFound },
    { std::filesystem::file_type::regular,      FileSystem::EFileType::Regular },
    { std::filesystem::file_type::directory,    FileSystem::EFileType::Directory },
    { std::filesystem::file_type::symlink,      FileSystem::EFileType::SymbolicLink },
    { std::filesystem::file_type::block,        FileSystem::EFileType::Block },
    { std::filesystem::file_type::character,    FileSystem::EFileType::Character },
    { std::filesystem::file_type::fifo,         FileSystem::EFileType::FirstInFirstOut },
    { std::filesystem::file_type::socket,       FileSystem::EFileType::Socket },
    { std::filesystem::file_type::unknown,      FileSystem::EFileType::Unknown }
};


// TODO: Use a better ID pooling solution

/// @brief Directory enumerators
static std::map<cell, std::filesystem::directory_iterator> directoryEnumerators;

/// @brief Available directory enumerator ID
static cell availableDirectoryEnumeratorID(0);

/// @brief Does file system object exist
/// @param amx AMX
/// @param params Function parameters
/// @return "1" if file exists, otherwise "0"
cell AMX_NATIVE_CALL FileSystem::Natives::DoesExist(AMX* amx, cell* params)
{
    return static_cast<cell>(std::filesystem::exists(amx_GetCppString(amx, params[1])));
}

/// @brief Create directory
/// @param amx AMX
/// @param params Function parameters
/// @return "1" if directory was successfully created, otherwise "0"
cell AMX_NATIVE_CALL FileSystem::Natives::CreateDirectory(AMX* amx, cell* params)
{
    cell ret(0);
    try
    {
        ret = params[2] ? std::filesystem::create_directories(amx_GetCppString(amx, params[1])) : std::filesystem::create_directory(amx_GetCppString(amx, params[1]));
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        logprintf(e.what());
    }
    return ret;
}

/// @brief Remove directory
/// @param amx AMX
/// @param params Function parameters
/// @return "1" if directory was successfully removed, otherwise "0"
cell AMX_NATIVE_CALL FileSystem::Natives::RemoveDirectory(AMX* amx, cell* params)
{
    cell ret(0);
    try
    {
        ret = params[2] ? static_cast<cell>(std::filesystem::remove_all(amx_GetCppString(amx, params[1]))) : static_cast<cell>(std::filesystem::remove(amx_GetCppString(amx, params[1])));
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        logprintf(e.what());
    }
    return ret;
}

/// @brief Create directory enumerator
/// @param amx AMX
/// @param params Function parameters
/// @return Directory enumerator ID if successful, otherwise "FileSystem::Natives::INVALID_DIRECTORY_ENUMERATOR_ID"
cell AMX_NATIVE_CALL FileSystem::Natives::CreateDirectoryEnumerator(AMX* amx, cell* params)
{
    cell ret(INVALID_DIRECTORY_ENUMERATOR_ID);
    std::filesystem::path path(amx_GetCppString(amx, params[1]));
    if (std::filesystem::is_directory(path))
    {
        directoryEnumerators.insert(std::pair<cell, std::filesystem::directory_iterator>(availableDirectoryEnumeratorID, std::filesystem::directory_iterator(path)));
        ret = availableDirectoryEnumeratorID;
        ++availableDirectoryEnumeratorID;
    }
    return ret;
}

/// @brief Enumerate directory
/// @param amx AMX
/// @param params Function parameters
/// @return "1" if enumeration was successful, otherwise "0"
cell AMX_NATIVE_CALL FileSystem::Natives::EnumerateDirectory(AMX* amx, cell* params)
{
    cell ret(0);
    const std::map<cell, std::filesystem::directory_iterator>::iterator& iterator(directoryEnumerators.find(params[1]));
    if (iterator != directoryEnumerators.end())
    {
        std::filesystem::directory_iterator& directory_iterator(iterator->second);
        std::filesystem::directory_iterator end;
        if (directory_iterator != end)
        {
            cell* type_out;
            amx_GetAddr(amx, params[2], &type_out);
            *type_out = static_cast<cell>(fileTypeLookup.at(directory_iterator->status().type()));
            amx_SetCppString(amx, params[3], directory_iterator->path().string(), params[4]);
            directory_iterator++;
            ret = 1;
        }
    }
    return ret;
}

/// @brief Destroy directory enumerator
/// @param amx AMX
/// @param params Function parameters
/// @return "1" if directory enumerator was successfully destroyed, otherwise "0"
cell AMX_NATIVE_CALL FileSystem::Natives::DestroyDirectoryEnumerator(AMX* amx, cell* params)
{
    cell ret(1);
    const std::map<cell, std::filesystem::directory_iterator>::iterator& iterator(directoryEnumerators.find(params[1]));
    if (iterator != directoryEnumerators.end())
    {
        directoryEnumerators.erase(iterator);
        ret = 0;
    }
    return ret;
}

/// @brief Move file
/// @param amx AMX
/// @param params Function parameters
/// @return "1" if file was moved successfully, otherwise "0"
cell AMX_NATIVE_CALL FileSystem::Natives::MoveFile(AMX* amx, cell* params)
{
    cell ret(-1);
    try
    {
        std::filesystem::rename(amx_GetCppString(amx, params[1]), amx_GetCppString(amx, params[2]));
        ret = 0;
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        logprintf(e.what());
    }
    return ret;
}

/// @brief Copy file
/// @param amx AMX
/// @param params Function parameters
/// @return "1" if file was copied successfully, otherwise "0"
cell AMX_NATIVE_CALL FileSystem::Natives::CopyFile(AMX* amx, cell* params)
{
    cell ret(-1);
    try
    {
        std::filesystem::copy(amx_GetCppString(amx, params[1]), amx_GetCppString(amx, params[2]));
        ret = 0;
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        logprintf(e.what());
    }
    return ret;
}

/// @brief Get path separator
/// @param amx AMX
/// @param params Function parameters
/// @return Path seperator
cell AMX_NATIVE_CALL FileSystem::Natives::GetPathSeparator(AMX* amx, cell* params)
{
    return std::filesystem::path::preferred_separator;
}

/// @brief Combine paths
/// @param amx AMX
/// @param params Function parameters
/// @return Nothing
cell AMX_NATIVE_CALL FileSystem::Natives::CombinePaths(AMX* amx, cell* params)
{
    amx_SetCppString(amx, params[3], std::filesystem::path(amx_GetCppString(amx, params[1])).append(amx_GetCppString(amx, params[2])).string(), params[4]);
    return 0;
}

/// @brief Get file name
/// @param amx AMX
/// @param params Function parameters
/// @return Nothing
cell AMX_NATIVE_CALL FileSystem::Natives::GetFileName(AMX* amx, cell* params)
{
    amx_SetCppString(amx, params[2], std::filesystem::path(amx_GetCppString(amx, params[1])).filename().string(), params[3]);
    return 0;
}

/// @brief Get directory path
/// @param amx AMX
/// @param params Function parameters
/// @return Nothing
cell AMX_NATIVE_CALL FileSystem::Natives::GetDirectoryPath(AMX* amx, cell* params)
{
    std::filesystem::path path(amx_GetCppString(amx, params[1]));
    amx_SetCppString(amx, params[2], path.has_parent_path() ? path.parent_path().make_preferred().string() : std::string("."), params[3]);
    return 0;
}

/// @brief Get file extension
/// @param amx AMX
/// @param params Function parameters
/// @return Nothing
cell AMX_NATIVE_CALL FileSystem::Natives::GetFileExtension(AMX* amx, cell* params)
{
    std::filesystem::path path(amx_GetCppString(amx, params[1]));
    amx_SetCppString(amx, params[2], path.has_extension() ? path.extension().string() : std::string(), params[3]);
    return 0;
}
