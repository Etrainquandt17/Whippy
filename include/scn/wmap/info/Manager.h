#ifndef SCN_WMAP_INFO_MANAGER_H
#define SCN_WMAP_INFO_MANAGER_H

#include "types.h"

namespace scn {
namespace wmap {
namespace info {

// TODO: members; only what scn::wmap::hero::InactiveHero calls.
class HeroPanel {
public:
    void charaDecideEffectAppear();
};

class Main {
public:
    HeroPanel& heroPanel(u32 index);
};

class Manager {
public:
    Main& main();
};

}
}
}

#endif
