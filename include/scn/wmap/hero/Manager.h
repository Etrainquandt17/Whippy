#ifndef SCN_WMAP_HERO_MANAGER_H
#define SCN_WMAP_HERO_MANAGER_H

#include "types.h"

namespace scn {
namespace step {
class ContextHeroIndivi;
}

namespace wmap {
namespace hero {

// TODO: members; only what scn::wmap::hero::InactiveHero uses.
class ShareData {
public:
    void decRestPlayer();

    u32 _0;
    int _4;
};

class Manager {
public:
    void createHero(u32 index, const step::ContextHeroIndivi& context);
    void setHitPointHalf(u32 index);

    ShareData& shareData() { return mShareData; }

private:
    u32 _0[15];
    ShareData mShareData;
};

}
}
}

#endif
