// fsutil implements a set of file system utility functions for Pawn.

#if defined _inc_fsutil
    #undef _inc_fsutil
#endif

#if defined _fsutil_included
    #endinput
#endif
#define _fsutil_included

/// @brief File type enumerator
enum ENTRY_TYPE
{
    /// @brief No file type
    E_NONE,

    /// @brief File not found
    E_NOT_FOUND,

    /// @brief Is regular file type
    E_REGULAR,

    /// @brief Is directory file type
    E_DIRECTORY,

    /// @brief Is symbolic link file type
    E_SYMBOLIC_LINK,

    /// @brief Is block file type
    E_BLOCK,

    /// @brief Is character file type
    E_CHARACTER,

    /// @brief Is "first in, first out" file type
    E_FIRST_IN_FIRST_OUT,

    /// @brief Socket file type
    E_SOCKET,

    /// @brief Unknown file type
    E_UNKNOWN
}

// Invalid directory enumerator ID
const Directory:INVALID_DIRECTORY_ENUMERATOR_ID = Directory:-1;


// Checks if an entry exists, works on files and directories.
native bool:Exists(const path[]);


// -
// Directories
// -

native CreateDir(const path[], bool:createBaseDirectories = true);
native RemoveDir(const path[], bool:recursive = false);
native Directory:OpenDir(const path[]);
native bool:DirNext(Directory:dir, &ENTRY_TYPE:type, entry[], len = sizeof entry);
native CloseDir(Directory:dir);


// -
// Move and Copy
// -

native MoveFile(const from[], const to[]);
native CopyFile(const from[], const to[]);


// -
// Path Functions
// -

// PathSep returns the directory separator character for the current runtime platform.
native PathSep();

// Joins two path components with a single `/` separator. Strips any trailing separators from `a`
// and any leading separators from `b`.
native PathJoin(const a[], const b[], output[], len = sizeof(output));

// Outputs the final component of a path, such as the file name without the directory.
native PathBase(const input[], output[], len = sizeof(output));

// Outputs all but the final component of a path, for example joining the output of this with the
// output of `PathBase` would result in the same path.
native PathDir(const input[], output[], len = sizeof(output));

// PathExt returns the extension of the final component of a path, this is the last token after a
// dot character, so `file.tar.gz` would output `.gz`.
native PathExt(const input[], output[], len = sizeof(output));
