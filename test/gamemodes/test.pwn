#define RUN_TESTS

#include <a_samp>
#include <YSI\y_testing>

#include "../../fsutil.inc"

main() {
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
