#include <a_samp>

#include "../../fsutil.inc"

main() {
    test("/");
    test("/samp");
    test("/samp/");
    test("/samp/gamemodes");
    test("/samp/filterscripts");
    test("/samp/plugins");
    test("/samp/scriptfiles");
    test("/samp/announce");
    test("/samp/samp03svr");
    test("/samp/samp-npc");
    test("/samp/samp.json");
    test("/samp/server.cfg");

// /: 0
// /samp: 0
// /samp/: 0
// /samp/gamemodes: 1
// /samp/filterscripts: 1
// /samp/plugins: 1
// /samp/scriptfiles: 1
// /samp/announce: 0
// /samp/samp03svr: 0
// /samp/samp-npc: 0
// /samp/samp.json: 1
// /samp/server.cfg: 0

}

test(name[]) {
    printf("%s: %d", name, Exists(name)); // stat(2)
}
