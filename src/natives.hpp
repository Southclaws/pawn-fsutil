#ifndef FSUTIL_NATIVES_H
#define FSUTIL_NATIVES_H

#include <amx/amx.h>

namespace Native {
cell Exists(AMX* amx, cell* params);

cell CreateDir(AMX* amx, cell* params);
cell RemoveDir(AMX* amx, cell* params);
cell OpenDir(AMX* amx, cell* params);
cell DirNext(AMX* amx, cell* params);
cell CloseDir(AMX* amx, cell* params);

cell MoveFile(AMX* amx, cell* params);
cell CopyFile(AMX* amx, cell* params);

cell PathSep(AMX* amx, cell* params);
cell PathJoin(AMX* amx, cell* params);
cell PathBase(AMX* amx, cell* params);
cell PathDir(AMX* amx, cell* params);
cell PathExt(AMX* amx, cell* params);
};

#endif
