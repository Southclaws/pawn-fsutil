#include <string>
using std::string;

#include <amx/amx2.h>

#include "impl.hpp"
#include "natives.hpp"

cell AMX_NATIVE_CALL Native::Exists(AMX* amx, cell* params)
{
    string path = amx_GetCppString(amx, params[1]);
    return Impl::Exists(path);
}

cell AMX_NATIVE_CALL Native::CreateDir(AMX* amx, cell* params)
{
    return 0;
}

cell AMX_NATIVE_CALL Native::RemoveDir(AMX* amx, cell* params)
{
    return 0;
}

cell AMX_NATIVE_CALL Native::ListDir(AMX* amx, cell* params)
{
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
