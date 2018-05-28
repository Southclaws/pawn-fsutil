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
memory.

`MoveFile` and `CopyFile` do exactly what you expect.

### Path Functions

There are also a handful of helper functions for working with file paths:

* `PathSep`
* `PathJoin`
* `PathBase`
* `PathDir`
* `PathExt`

See the source code for documentation.

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
