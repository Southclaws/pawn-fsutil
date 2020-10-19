// fsutil implements a set of file system utility functions for Pawn.

const ENTRY_TYPE:E_REGULAR = ENTRY_TYPE:2;
const ENTRY_TYPE:E_DIRECTORY = ENTRY_TYPE:3;


// Checks if an entry exists, works on files and directories.
native bool:Exists(const path[]);


// -
// Directories
// -

native CreateDir(const path[]);
native RemoveDir(const path[], bool:recursive = false);
native Directory:OpenDir(const path[]);
native bool:DirNext(Directory:dir, &ENTRY_TYPE:type, entry[], len = sizeof(entry));
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
