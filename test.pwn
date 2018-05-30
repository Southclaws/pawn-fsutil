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
    new testDir[] = "scriptfiles/OpenDir";
    new ret;

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
        entry[256],
        ENTRY_TYPE:type,
        bool:b;

    b = DirNext(dir, type, entry);
    printf("DirNext: %d, %d, %s", b, _:type, entry);
    ASSERT(b == true);
    ASSERT(!strcmp(entry, "scriptfiles\\OpenDir\\a"));
    ASSERT(type == E_REGULAR);

    b = DirNext(dir, type, entry);
    printf("DirNext: %d, %d, %s", b, _:type, entry);
    ASSERT(b == true);
    ASSERT(!strcmp(entry, "scriptfiles\\OpenDir\\b"));
    ASSERT(type == E_REGULAR);

    b = DirNext(dir, type, entry);
    printf("DirNext: %d, %d, %s", b, _:type, entry);
    ASSERT(b == true);
    ASSERT(!strcmp(entry, "scriptfiles\\OpenDir\\c"));
    ASSERT(type == E_REGULAR);

    b = DirNext(dir, type, entry);
    printf("DirNext: %d, %d, %s", b, _:type, entry);
    ASSERT(b == true);
    ASSERT(!strcmp(entry, "scriptfiles\\OpenDir\\d"));
    ASSERT(type == E_DIRECTORY);

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
}

Test:PathBaseLongUnix() {
    new output[256];
    PathBase("scriptfiles/someFolder/another/file.png", output);

    ASSERT(!strcmp(output, "file.png"));
}

Test:PathBaseLongWindows() {
    new output[256];
    PathBase("scriptfiles\\someFolder\\another\\file.png", output);

    ASSERT(!strcmp(output, "file.png"));
}

Test:PathBase() {
    new output[256];
    PathBase(".\\scriptfiles\\languages\\Russian", output);

    ASSERT(!strcmp(output, "Russian"));
}

Test:PathBaseJustFile() {
    new output[256];
    PathBase("file.png", output);

    ASSERT(!strcmp(output, "file.png"));
}

Test:PathBaseEmpty() {
    new output[256];
    PathBase("", output);

    ASSERT(!strcmp(output, ""));
}

Test:PathBaseDot() {
    new output[256];
    PathBase(".", output);

    ASSERT(!strcmp(output, ""));
}

Test:PathDir() {
    new wantOutput[256];
    format(wantOutput, sizeof wantOutput, "scriptfiles%csomeFolder%canother", Separator, Separator);

    new output[256];
    PathDir("scriptfiles/someFolder/another/file.png", output);
    ASSERT(!strcmp(output, wantOutput));
}

Test:PathDirNoParent() {
    new output[256];
    PathDir("file.png", output);
    ASSERT(!strcmp(output, "."));
}

Test:PathExt() {
    new output[256];
    PathExt("file.png", output);
    ASSERT(!strcmp(output, ".png"));
}

Test:PathExtMulti() {
    new output[256];
    PathExt("file.tar.gz", output);
    ASSERT(!strcmp(output, ".gz"));
}

Test:PathExtNone() {
    new output[256];
    PathExt("file", output);
    ASSERT(!strcmp(output, ""));
}
