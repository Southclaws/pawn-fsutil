#include <amx/amx.h>
#include <plugincommon.h>

#include "common.hpp"
#include "natives.hpp"

logprintf_t logprintf;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData)
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
}

AMX_NATIVE_INFO NATIVES[] = {
    { "Exists", Native::Exists },

    { "CreateDir", Native::CreateDir },
    { "RemoveDir", Native::RemoveDir },
    { "OpenDir", Native::OpenDir },
    { "DirNext", Native::DirNext },
    { "CloseDir", Native::CloseDir },

    { "MoveFile", Native::MoveFile },
    { "CopyFile", Native::CopyFile },

	{ "PathSep", Native::PathSep },
    { "PathJoin", Native::PathJoin },
    { "PathBase", Native::PathBase },
    { "PathDir", Native::PathDir },
    { "PathExt", Native::PathExt },

    { 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx)
{
    return amx_Register(amx, NATIVES, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx)
{
    return AMX_ERR_NONE;
}
