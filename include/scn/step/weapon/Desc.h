#ifndef SCN_STEP_WEAPON_DESC_H
#define SCN_STEP_WEAPON_DESC_H

#include "hel/math/Vector2.h"
#include "scn/step/ostop/Flag.h"
#include "scn/step/weapon/Kind.h"
#include "types.h"

namespace ocoll {

class Owner;

}

namespace scn {
namespace step {
namespace weapon {

// TODO: name the members.
class Desc {
public:
    Desc();
    Desc(Kind kind, u32 variation, ostop::Flag flag, const hel::math::Vector2& pos, const hel::math::Vector2& _14,
         ::ocoll::Owner& owner);
    Desc(Kind kind, u32 variation, ostop::Flag flag, const hel::math::Vector2& pos, const hel::math::Vector2& _14,
         const hel::math::Vector2& _1c, ::ocoll::Owner& owner);

    Kind mKind;
    u32 mVariation;
    ostop::Flag mFlag;
    hel::math::Vector2 mPos;
    hel::math::Vector2 _14;
    hel::math::Vector2 _1c;
    hel::math::Vector2 _24;
    bool _2c;
    bool _2d;
    bool _2e;
    bool _2f;
    u32 _30;
    ::ocoll::Owner* mOwner;
};

}
}
}

#endif
