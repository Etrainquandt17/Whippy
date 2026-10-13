#ifndef SCN_STEP_ENEMY_LOWPERBULLET_CUSTOM_H
#define SCN_STEP_ENEMY_LOWPERBULLET_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "hel/math/Vector3.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

}
namespace hero {

class Hero;

}
namespace enemy {
namespace lowperbullet {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::lowperbullet::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace lowperbullet {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);

    void requestWeaponLandHit();
    void requestWeaponBurst();
    hel::math::Vector3 getTargetHeroPos();
    void setTargetHero(util::ObjRefHandle<hero::Hero> hero);
    void setParent(boss::Boss& boss, u32 index);

private:
    u32 _8[9];
};

}
}
}
}

#endif
