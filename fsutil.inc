// fsutil implements a set of file system utility functions for Pawn.

enum ENTRY_TYPE {
    E_NOT_FOUND = -1,
    E_NONE,
    E_REGULAR,
    E_DIRECTORY,
    E_SYMLINK,
	E_BLOCK,
    E_CHARACTER,
    E_FIFO,
    E_SOCKET,
    E_UNKNOWN
}

native bool:Exists(path[]);
native CreateDir(path[]);
native RemoveDir(path[], bool:recursive = false);
native Directory:OpenDir(path[]);
native bool:DirNext(Directory:dir, &ENTRY_TYPE:type, entry[], len = sizeof(entry));
native CloseDir(Directory:dir);
