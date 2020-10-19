#include <amx/amx.h>
#include <plugincommon.h>

#include "common.hpp"
#include "natives.hpp"

logprintf_t logprintf;

AMX_NATIVE_INFO NATIVES[] =
{
    { "Exists", FileSystem::Natives::DoesExist },

    { "CreateDir", FileSystem::Natives::CreateDirectory },
    { "RemoveDir", FileSystem::Natives::RemoveDirectory },
    { "OpenDir", FileSystem::Natives::CreateDirectoryEnumerator },
    { "DirNext", FileSystem::Natives::EnumerateDirectory },
    { "CloseDir", FileSystem::Natives::DestroyDirectoryEnumerator },

    { "MoveFile", FileSystem::Natives::MoveFile },
    { "CopyFile", FileSystem::Natives::CopyFile },

    { "PathSep", FileSystem::Natives::GetPathSeparator },
    { "PathJoin", FileSystem::Natives::CombinePaths },
    { "PathBase", FileSystem::Natives::GetFileName },
    { "PathDir", FileSystem::Natives::GetDirectoryPath },
    { "PathExt", FileSystem::Natives::GetFileExtension },

    { 0, 0 }
};

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData)
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = static_cast<logprintf_t>(ppData[PLUGIN_DATA_LOGPRINTF]);
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
    // ...
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx)
{
    return amx_Register(amx, NATIVES, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx)
{
    return AMX_ERR_NONE;
}
