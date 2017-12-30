#ifndef FSUTIL_NATIVES_H
#define FSUTIL_NATIVES_H

#include <amx/amx.h>

namespace Native {
cell Exists(AMX* amx, cell* params);

cell CreateDir(AMX* amx, cell* params);
cell RemoveDir(AMX* amx, cell* params);
cell ListDir(AMX* amx, cell* params);

cell MoveFile(AMX* amx, cell* params);
cell CopyFile(AMX* amx, cell* params);
};

#endif
