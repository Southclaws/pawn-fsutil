#define RUN_TESTS

#include "fsutil.inc"

#include <a_samp>
#include <YSI\y_testing>


new Separator;

main() {
    Separator = PathSep();
    printf("Platform specific directory separator: '%c'", Separator);
}

Test:Exists() {
    ASSERT(Exists("scriptfiles"));
    ASSERT(Exists("scriptfiles/somefile"));
    ASSERT(Exists("server.cfg"));
    ASSERT(Exists("server_log.txt"));
}

Test:CreateDir() {
    new testDir[] = "scriptfiles/CreateDir";

    if(Exists(testDir)) {
        ASSERT(RemoveDir(testDir) == 1);
    }

    new ret = CreateDir(testDir);
    ASSERT(ret == 1);
    ASSERT(Exists(testDir));

    // cleanup
    ASSERT(RemoveDir(testDir) == 1);
}

Test:RemoveDir() {
    new testDir[] = "scriptfiles/RemoveDir";

    if(!Exists(testDir)) {
        ASSERT(CreateDir(testDir) == 1);
    }

    new ret = RemoveDir(testDir);
    ASSERT(ret == 1);
    ASSERT(!Exists(testDir));
}

Test:OpenDir() {
    new testDir[256];
    new ret;

    format(testDir, sizeof testDir, "scriptfiles%cOpenDir", Separator);

    if(!Exists(testDir)) {
        ASSERT(CreateDir(testDir) == 1);
        fclose(fopen("OpenDir/a", io_write));
        fclose(fopen("OpenDir/b", io_write));
        fclose(fopen("OpenDir/c", io_write));
        ASSERT(CreateDir("scriptfiles/OpenDir/d") == 1);
        ASSERT(Exists("scriptfiles/OpenDir/a"));
        ASSERT(Exists("scriptfiles/OpenDir/b"));
        ASSERT(Exists("scriptfiles/OpenDir/c"));
        ASSERT(Exists("scriptfiles/OpenDir/d"));
    }

    new Directory:dir = OpenDir(testDir);
    ASSERT(_:dir >= 0);

    new
        wantEntry[256],
        entry[256],
        ENTRY_TYPE:type,
        bool:b;

    format(wantEntry, sizeof wantEntry, "scriptfiles%cOpenDir%ca", Separator, Separator);
    b = DirNext(dir, type, entry);
    printf("DirNext: %d, %d, %s", b, _:type, entry);
    ASSERT(b == true);
    ASSERT(!strcmp(entry, wantEntry));
    printf("got  '%s'\nwant '%s'", entry, wantEntry);
    ASSERT(type == E_REGULAR);

    format(wantEntry, sizeof wantEntry, "scriptfiles%cOpenDir%cb", Separator, Separator);
    b = DirNext(dir, type, entry);
    printf("DirNext: %d, %d, %s", b, _:type, entry);
    ASSERT(b == true);
    ASSERT(!strcmp(entry, wantEntry));
    printf("got  '%s'\nwant '%s'", entry, wantEntry);
    ASSERT(type == E_REGULAR);

    format(wantEntry, sizeof wantEntry, "scriptfiles%cOpenDir%cc", Separator, Separator);
    b = DirNext(dir, type, entry);
    printf("DirNext: %d, %d, %s", b, _:type, entry);
    ASSERT(b == true);
    ASSERT(!strcmp(entry, wantEntry));
    printf("got  '%s'\nwant '%s'", entry, wantEntry);
    ASSERT(type == E_REGULAR);

    format(wantEntry, sizeof wantEntry, "scriptfiles%cOpenDir%cd", Separator, Separator);
    b = DirNext(dir, type, entry);
    printf("DirNext: %d, %d, %s", b, _:type, entry);
    ASSERT(b == true);
    ASSERT(!strcmp(entry, wantEntry));
    printf("got  '%s'\nwant '%s'", entry, wantEntry);
    ASSERT(type == E_DIRECTORY);

    b = DirNext(dir, type, entry);
    printf("DirNext: %d, %d, %s", b, _:type, entry);
    ASSERT(b == false);

    ret = CloseDir(dir);
    ASSERT(ret == 0);

    ret = RemoveDir(testDir, true);
    ASSERT(ret > 0);
    ASSERT(!Exists(testDir));
}

Test:MoveFile() {
    new
        from[] = "scriptfiles/MoveFileA",
        to[] = "scriptfiles/MoveFileB";

    if(!Exists(from)) {
        fclose(fopen("MoveFileA", io_write));
    }
    if(Exists(from)) {
        fremove("MoveFileB");
    }

    new ret = MoveFile(from, to);
    ASSERT(ret == 0);
    ASSERT(Exists(to));
    ASSERT(!Exists(from));

    fremove("MoveFileB");
}

Test:CopyFile() {
    new
        from[] = "scriptfiles/CopyFileA",
        to[] = "scriptfiles/CopyFileB";

    if(!Exists(from)) {
        fclose(fopen("CopyFileA", io_write));
    }
    if(Exists(from)) {
        fremove("CopyFileB");
    }

    new ret = CopyFile(from, to);
    ASSERT(ret == 0);
    ASSERT(Exists(to));
    ASSERT(Exists(from));

    fremove("CopyFileA");
    fremove("CopyFileB");
}

Test:PathJoin() {
    new
        a[] = "scriptfiles",
        b[] = "folderA";

    new wantOutput[256];
    format(wantOutput, sizeof wantOutput, "%s%c%s", a, Separator, b);

    new output[256];
    PathJoin(a, b, output);

    ASSERT(!strcmp(output, wantOutput));
    printf("got  '%s'\nwant '%s'", output, wantOutput);
}

Test:PathBaseLongUnix() {
    new wantOutput[256] = "file.png";
    new output[256];
    PathBase("scriptfiles/someFolder/another/file.png", output);

    ASSERT(!strcmp(output, wantOutput));
    printf("got  '%s'\nwant '%s'", output, wantOutput);
}

Test:PathBaseLongWindows() {
    new wantOutput[256] = "file.png";
    new output[256];
    PathBase("scriptfiles/someFolder/another/file.png", output);

    ASSERT(!strcmp(output, wantOutput));
    printf("got  '%s'\nwant '%s'", output, wantOutput);
}

Test:PathBase() {
    new wantOutput[256] = "Russian";
    new output[256];
    PathBase("./scriptfiles/languages/Russian", output);

    ASSERT(!strcmp(output, wantOutput));
    printf("got  '%s'\nwant '%s'", output, wantOutput);
}

Test:PathBaseJustFile() {
    new wantOutput[256] = "file.png";
    new output[256];
    PathBase("file.png", output);

    ASSERT(!strcmp(output, wantOutput));
    printf("got  '%s'\nwant '%s'", output, wantOutput);
}

Test:PathBaseEmpty() {
    new wantOutput[256] = "";
    new output[256];
    PathBase("", output);

    ASSERT(!strcmp(output, wantOutput));
    printf("got  '%s'\nwant '%s'", output, wantOutput);
}

Test:PathBaseDot() {
    new wantOutput[256] = "";
    new output[256];
    PathBase(".", output);

    ASSERT(!strcmp(output, wantOutput));
    printf("got  '%s'\nwant '%s'", output, wantOutput);
}

Test:PathDir() {
    new wantOutput[256];
    format(wantOutput, sizeof wantOutput, "scriptfiles%csomeFolder%canother", Separator, Separator);

    new output[256];
    PathDir("scriptfiles/someFolder/another/file.png", output);
    ASSERT(!strcmp(output, wantOutput));
    printf("got  '%s'\nwant '%s'", output, wantOutput);
    printf("got  '%s'\nwant '%s'", output, wantOutput);
}

Test:PathDirNoParent() {
    new wantOutput[256] = ".";
    new output[256];
    PathDir("file.png", output);
    ASSERT(!strcmp(output, wantOutput));
    printf("got  '%s'\nwant '%s'", output, wantOutput);
}

Test:PathExt() {
    new wantOutput[256] = ".png";
    new output[256];
    PathExt("file.png", output);
    ASSERT(!strcmp(output, wantOutput));
    printf("got  '%s'\nwant '%s'", output, wantOutput);
}

Test:PathExtMulti() {
    new wantOutput[265] = ".gz";
    new output[256];
    PathExt("file.tar.gz", output);
    ASSERT(!strcmp(output, wantOutput));
    printf("got  '%s'\nwant '%s'", output, wantOutput);
}

Test:PathExtNone() {
    new wantOutput[265] = "";
    new output[256];
    PathExt("file", output);
    ASSERT(!strcmp(output, wantOutput));
    printf("got  '%s'\nwant '%s'", output, wantOutput);
}
