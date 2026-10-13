#include "scn/step/hero/highjump/StateRocketFall.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
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
#include "scn/step/hero/highjump/StateRocketFallEnd.h"
#include "scn/step/hero/highjump/StateRocketFallWallHit.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace highjump {

StateRocketFall::StateRocketFall(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mSpeedRate(1.0f)
    , mStartPos(static_cast<const Hero&>(obj()).location().pos())
    , _1C(false) {
    obj().piggyback().unlinkAll();
    obj().footState().setAir();
    obj().invincible().setPerm();
    obj().move().setSpeedV(obj().param().highjump()._80);
    obj().move().resetSpeedH();
    obj().model().script().start(0xFB);
}

StateRocketFall::~StateRocketFall() {
}

void StateRocketFall::procAnim() {
    const HighjumpParam& param = obj().param().highjump();
    mFrame++;
    if (mFrame >= param._84) {
        obj().stateChanger().setNextState<StateRocketFallEnd, Hero*>(objPtr());
        return;
    }
    hel::math::Vector2 velocity = obj().move().velocity().getXY();
    if (!velocity.isZero()) {
        velocity.normalize();
        f32 angle = hel::math::Vector2::BASIS_Y.signedAngle(velocity);
        obj().model().modelRotCtrl().setRotV(57.29578f * angle - 180.0f);
    }
    if (!_1C) {
        hel::math::Vector3 pos = static_cast<const Hero&>(obj()).location().pos();
        if (pos.y - mStartPos.y < param._88) {
            mFrame += param._8C;
            _1C = true;
        }
    }
}

void StateRocketFall::procMove() {
    const HighjumpParam& param = obj().param().highjump();
    if (mFrame > param._90) {
        mSpeedRate *= param._94;
    }
    hel::math::Vector3 velocity = obj().move().velocity();
    f32 maxSpeedH = param._7C;
    velocity.y = param._80;
    if (Utility::IsPressHDirKey(obj())) {
        Utility::UpdateMoveTarget(obj());
        velocity.x += param._98 * obj().target().getSign();
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

void StateRocketFall::procFixPos() {
    if (mFrame > 1) {
        if (!obj().objColl().objColl().attack().isCollideGimmick()) {
            MapCollResult result = obj().mapColl().result();
            if (result.mIsHitFloor) {
                obj().stateChanger().setNextState<StateRocketFallWallHit, Hero*>(objPtr());
            }
        }
    }
}

}}}}  // namespace scn::step::hero::highjump
