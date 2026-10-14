#include "scn/step/hero/highjump/StateJump.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/HighjumpParam.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/MapCollResult.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/highjump/StateJumpEnd.h"
#include "scn/step/hero/highjump/StateRoofHit.h"
#include "util/StateChanger.h"

using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace highjump {

StateJump::StateJump(Hero* hero, JumpKind kind)
    : StateBase(hero)
    , mFrame(0)
    , mSpeedRate(1.0f)
    , mStartPos(static_cast<const Hero&>(obj()).location().pos())
    , _1C(false)
    , mKind(kind)
    , mIsEnd(false) {
    obj().piggyback().unlinkAll();
    obj().footState().setAir();
    obj().invincible().setPerm();
    obj().move().setSpeedV(param()._4);
    obj().move().resetSpeedH();
    obj().mapColl().setIgnoreInvisibleRoof(false);
    u32 script = 0xF5;
    if (mKind == JUMP_KIND_1) {
        script = 0xF6;
    }
    if (mKind == JUMP_KIND_2) {
        script = 0xF7;
    }
    obj().model().script().start(script);
}

StateJump::~StateJump() {
    if (!mIsEnd && mKind == JUMP_KIND_0) {
        obj().effect()._8.releaseAndVanish();
        obj().effect()._58.releaseAndVanish();
    }
    obj().mapColl().setIgnoreInvisibleRoof(true);
}

void StateJump::procAnim() {
    mFrame++;
    if (mFrame >= param()._8) {
        obj().stateChanger().setNextState<StateJumpEnd, Hero*>(objPtr());
        mIsEnd = true;
        return;
    }
    Vector2 velocity = obj().move().velocity().getXY();
    if (!velocity.isZero()) {
        velocity.normalize();
        f32 angle = Vector2::BASIS_Y.signedAngle(velocity);
        obj().model().modelRotCtrl().setRotV(57.29578f * angle);
    }
    if (!_1C) {
        Vector3 pos = static_cast<const Hero&>(obj()).location().pos();
        if (pos.y - mStartPos.y > param()._C) {
            mFrame += param()._10;
            _1C = true;
        }
    }
}

void StateJump::procMove() {
    if (mFrame > param()._14) {
        mSpeedRate *= param()._18;
    }
    Vector3 velocity = obj().move().velocity();
    f32 maxSpeedH = param()._0;
    velocity.y = param()._4;
    if (Utility::IsPressHDirKey(obj())) {
        Utility::UpdateMoveTarget(obj());
        velocity.x += obj().target().getSign() * param()._1C;
        if (velocity.x > maxSpeedH) {
            velocity.x = maxSpeedH;
        }
        if (velocity.x < -maxSpeedH) {
            velocity.x = -maxSpeedH;
        }
    }
    velocity *= mSpeedRate;
    obj().move().setVelocity(velocity);
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateJump::procFixPos() {
    if (mKind == JUMP_KIND_2) {
        MapCollResult result = obj().mapColl().result();
        if (mFrame > 1) {
            if (!obj().objColl().objColl().attack().isCollideGimmick()) {
                if (result.mIsHitRoof || obj().worldCage().getCorrectedDiff().y < 0.0f) {
                    obj().stateChanger().setNextState<StateRoofHit, Hero*>(objPtr());
                    mIsEnd = true;
                }
            }
        }
    }
}

const HighjumpParamJump& StateJump::param() const {
    const HighjumpParam& param = obj().param().highjump();
    switch (mKind) {
    case JUMP_KIND_0:
        return param._0[0];
    case JUMP_KIND_1:
        return param._0[1];
    case JUMP_KIND_2:
        return param._0[2];
    }
    return param._0[0];
}

}}}}  // namespace scn::step::hero::highjump
