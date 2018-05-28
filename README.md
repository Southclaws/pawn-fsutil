# fsutil

fsutil is a file system utility plugin for Pawn.

Provides a simple API for checking existence, creating, reading and removing
directories and moving/copying files or directories.

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

`Exists`, `CreateDir`, `RemoveDir` are self explanatory. `Exists` works on files
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

### Path Functions

There are also a handful of helper functions for working with file paths:

* `PathSep`
* `PathJoin`
* `PathBase`
* `PathDir`
* `PathExt`

See the source code for documentation.

## Testing

To run unit tests for Windows, first build the plugin with Visual Studio. If you
use "Open CMake" mode, the `.dll` file will be output directly to the `plugins`
directory of the test runtime. If you use cmake to generate a solution file, the
`.dll` file will probably be in a directory inside `plugins` named `Release` (or
`Debug`) so you'll have to copy that out first with
`cp test/plugins/Release/fsutil.dll test/plugins/fsutil.dll`.

```powershell
make test-windows
```

Linux testing can be done on Windows if you have Docker installed. The following
command just runs the same as the `test-windows` but with `--container`
activated to vitualise a Linux environment.

```bash
make test-linux
```
