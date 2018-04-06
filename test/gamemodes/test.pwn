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
        ASSERT(RemoveDir(testDir) == 0);
    }

    new ret = CreateDir(testDir);
    ASSERT(ret == 1);
    ASSERT(Exists(testDir));

    // cleanup
    ASSERT(RemoveDir(testDir) == 0);
}

Test:RemoveDir() {
    new testDir[] = "scriptfiles/RemoveDir";

    if(!Exists(testDir)) {
        ASSERT(CreateDir(testDir) == 1);
    }

    new ret = RemoveDir(testDir);
    ASSERT(ret == 0);
    ASSERT(!Exists(testDir));
}