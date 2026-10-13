#ifndef SCN_STEP_BOSS_COMMON_STATEJUMP_H
#define SCN_STEP_BOSS_COMMON_STATEJUMP_H

#include "gobj/MoveParam.h"
#include "hel/math/Vec2.h"
#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/ocoll/AttackType.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace common {

// TODO: name the members.
struct StateJumpDesc {
    // TODO: name the types.
    enum LandingAnimType {
        LANDING_ANIM_TYPE_0,
    };

    StateJumpDesc(hel::math::Vector2, gobj::MoveParamDecel, gobj::MoveParamDecel, gobj::MoveParamFall, hel::math::Vector2, hel::math::Vector2, bool,
                  LandingAnimType, bool, ocoll::AttackType);

    hel::math::Vector2 _0;
    gobj::MoveParamDecel _8;
    gobj::MoveParamDecel _C;
    gobj::MoveParamFall _10;
    hel::math::Vec2 _1C;
    hel::math::Vec2 _24;
    bool _2C;
    LandingAnimType _30;
    bool _34;
    ocoll::AttackType _38;
};

class StateJump : public StateBase {
public:
    StateJump(Boss* boss, StateJumpDesc& desc, u32 scriptKind);
    virtual ~StateJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    StateJumpDesc& mDesc;
};

class StateJumpStart : public StateBase {
public:
    StateJumpStart(Boss* boss, StateJumpDesc& desc, u32 scriptKind0, u32 scriptKind1);
    virtual ~StateJumpStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mScriptKind;
    StateJumpDesc& mDesc;
};

}
}
}
}

#endif
