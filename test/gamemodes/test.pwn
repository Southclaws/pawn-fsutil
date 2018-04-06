#define RUN_TESTS

#include <a_samp>
#include <YSI\y_testing>

#include "../../fsutil.inc"

main() {
    test("scriptfiles/somefile");
    test("server.cfg");
}

test(name[]) {
    printf("%s: %d", name, Exists(name)); // stat(2)
}

Test:Exists() {
    ASSERT(Exists("scriptfiles"));
    ASSERT(Exists("scriptfiles/somefile"));
    ASSERT(Exists("server.cfg"));
    ASSERT(Exists("server_log.txt"));
}