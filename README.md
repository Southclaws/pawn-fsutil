# fsutil

fsutil is a file system utility plugin for Pawn.

## Installation

Simply install to your project:

```bash
sampctl package install Southclaws/samp-fsutil
```

Include in your code and begin using the library:

```pawn
#include <fsutil>
```

## Usage

`Exists`, `CreateDir`, `RemoveDir` are self explanitory. `Exists` works on files
and directories.

`OpenDir` opens a directory ready for iterating, each `DirNext` call will
iterate through the directory, use it like
`while(DirNext(dir, type, entry) { ...` where `type` and `entry` are pass by
reference. When you're done, use `CloseDir` to close the directory and free
memory:

```pawn
new
    Directory:dir = OpenDir(testDir),
    entry[256],
    ENTRY_TYPE:type;

while(DirNext(dir, type, entry)) {
    if(type == E_REGULAR) {
        printf("File: %s", entry);
    } else if(type == E_DIRECTORY) {
        printf("Directory: %s", entry);
    } else {
        printf("Something else: %s", entry);
    }
}

new ret = CloseDir(dir); // always close an open Directory
```

`MoveFile` and `CopyFile` do exactly what you expect.

## Testing

Run unit tests with:

### Windows

```powershell
make test-windows
```

### Linux

```bash
make test-debian
```
