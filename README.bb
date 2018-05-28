[COLOR="#FF4700"][SIZE="7"][B]fsutil[/B][/SIZE][/COLOR]

fsutil is a file system utility plugin for Pawn.

Provides a simple API for checking existence, creating, reading and removing directories and moving/copying files or directories.

[COLOR="RoyalBlue"][SIZE="6"][B]Installation[/B][/SIZE][/COLOR]

Simply install to your project:

[CODE]
sampctl package install Southclaws/samp-fsutil
[/CODE]

Include in your code and begin using the library:

[CODE]
[COLOR="Blue"]#include <fsutil>[/COLOR]
[/CODE]

[COLOR="RoyalBlue"][SIZE="6"][B]Usage[/B][/SIZE][/COLOR]

[FONT="courier new"]Exists[/FONT], [FONT="courier new"]CreateDir[/FONT], [FONT="courier new"]RemoveDir[/FONT] are self explanatory. [FONT="courier new"]Exists[/FONT] works on files and directories.

[FONT="courier new"]OpenDir[/FONT] opens a directory ready for iterating, each [FONT="courier new"]DirNext[/FONT] call will iterate through the directory, use it like [FONT="courier new"]while(DirNext(dir, type, entry) { ...[/FONT] where [FONT="courier new"]type[/FONT] and [FONT="courier new"]entry[/FONT] are pass by reference. When you’re done, use [FONT="courier new"]CloseDir[/FONT] to close the directory and free memory:

[CODE]
[COLOR="Blue"]new[/COLOR]
    Directory:dir = OpenDir(testDir),
    entry[[COLOR="Purple"]256[/COLOR]],
    ENTRY_TYPE:type;

while(DirNext(dir, type, entry)) {
    [COLOR="Blue"]if[/COLOR](type == E_REGULAR) {
        printf([COLOR="Purple"]"File: %s"[/COLOR], entry);
    } [COLOR="Blue"]else[/COLOR] [COLOR="Blue"]if[/COLOR](type == E_DIRECTORY) {
        printf([COLOR="Purple"]"Directory: %s"[/COLOR], entry);
    } [COLOR="Blue"]else[/COLOR] {
        printf([COLOR="Purple"]"Something [COLOR="Blue"]else[/COLOR]: %s"[/COLOR], entry);
    }
}

new ret = CloseDir(dir); [COLOR="Green"]// always close an open Directory[/COLOR]
[/CODE]

[FONT="courier new"]MoveFile[/FONT] and [FONT="courier new"]CopyFile[/FONT] do exactly what you expect.

[COLOR="DeepSkyBlue"][SIZE="5"][B]Path Functions[/B][/SIZE][/COLOR]

There are also a handful of helper functions for working with file paths:

[LIST]
[*][FONT="courier new"]PathSep[/FONT]
[*][FONT="courier new"]PathJoin[/FONT]
[*][FONT="courier new"]PathBase[/FONT]
[*][FONT="courier new"]PathDir[/FONT]
[*][FONT="courier new"]PathExt[/FONT]
[/LIST]

See the source code for documentation.

[COLOR="RoyalBlue"][SIZE="6"][B]Testing[/B][/SIZE][/COLOR]

To run unit tests for Windows, first build the plugin with Visual Studio. If you use “Open CMake” mode, the [FONT="courier new"].dll[/FONT] file will be output directly to the [FONT="courier new"]plugins[/FONT] directory of the test runtime. If you use cmake to generate a solution file, the [FONT="courier new"].dll[/FONT] file will probably be in a directory inside [FONT="courier new"]plugins[/FONT] named [FONT="courier new"]Release[/FONT] (or [FONT="courier new"]Debug[/FONT]) so you’ll have to copy that out first with [FONT="courier new"]cp test/plugins/Release/fsutil.dll test/plugins/fsutil.dll[/FONT].

[CODE]
make test-windows
[/CODE]

Linux testing can be done on Windows if you have Docker installed. The following command just runs the same as the [FONT="courier new"]test-windows[/FONT] but with [FONT="courier new"]--container[/FONT] activated to vitualise a Linux environment.

[CODE]
make test-linux
[/CODE]

