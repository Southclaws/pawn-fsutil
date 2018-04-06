#include <string>

#include <amx/amx2.h>

#include "impl.hpp"
#include "natives.hpp"

cell AMX_NATIVE_CALL Native::Exists(AMX* amx, cell* params)
{
    std::string path = amx_GetCppString(amx, params[1]);
    return Impl::Exists(path);
}

cell AMX_NATIVE_CALL Native::CreateDir(AMX* amx, cell* params)
{
    std::string path = amx_GetCppString(amx, params[1]);
    return Impl::CreateDir(path);
}

cell AMX_NATIVE_CALL Native::RemoveDir(AMX* amx, cell* params)
{
    std::string path = amx_GetCppString(amx, params[1]);
    return Impl::RemoveDir(path, params[2]);
}

cell AMX_NATIVE_CALL Native::OpenDir(AMX* amx, cell* params)
{
    std::string path = amx_GetCppString(amx, params[1]);
    return Impl::OpenDir(path);
}

cell AMX_NATIVE_CALL Native::DirNext(AMX* amx, cell* params)
{
    std::string entry;
    fs::file_type type;

    bool ret = Impl::DirNext(params[1], entry, type);

    cell* typeOut;
    amx_GetAddr(amx, params[2], &typeOut);
    *typeOut = (int)type;

    amx_SetCppString(amx, params[3], entry, params[4]);

    return 1;
}

cell AMX_NATIVE_CALL Native::CloseDir(AMX* amx, cell* params)
{
    std::string path = amx_GetCppString(amx, params[1]);
    return 0;
}

cell AMX_NATIVE_CALL Native::MoveFile(AMX* amx, cell* params)
{
    return 0;
}

cell AMX_NATIVE_CALL Native::CopyFile(AMX* amx, cell* params)
{
    return 0;
}
