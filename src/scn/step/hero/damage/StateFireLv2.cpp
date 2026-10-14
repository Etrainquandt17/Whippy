#include "scn/step/hero/damage/StateFireLv2.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/DamageFlash.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/damage/Utility.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace hero {
namespace damage {

StateFireLv2::StateFireLv2(Hero* hero)
    : StateBase(hero)
    , mRot(0.0f)
    , mIsLanded(false)
    , mWait(10)
    , mFrame(0) {
    obj().footState().setAir();
    obj().model().script().start(0x49);
    Utility::InitTarget(obj());
    Utility::InitVelocity(obj());
    obj().invincible().setPerm();
    obj().effect()._58.requestN(static_cast<effect::Kind>(0xDB), 1);
    obj().damageFlash().set(static_cast<ocoll::Element>(2));
}

StateFireLv2::~StateFireLv2() {
    obj().model().modelRotCtrl().setRotV(0.0f);
    obj().model().modelRotCtrl().setRotH(0.0f);
    obj().damageFlash().unset();
    obj().invincible().set(120);
}

void StateFireLv2::procAnim() {
    if (++mFrame >= 30) {
        hero::Utility::ChangeStateWaitOrFall(obj());
        return;
    }
    mRot += 20.0f * obj().target().getSign();
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    if (mRot < 0.0f) {
        mRot += 360.0f;
    }
    if (!mIsLanded) {
        Vector2 dir = obj().move().velocity().getXY();
        if (!dir.isZero()) {
            dir.normalize();
            f32 angle = Vector2::BASIS_Y.signedAngle(dir);
            obj().model().modelRotCtrl().setRotV(57.29578f * angle);
        }
        obj().model().modelRotCtrl().setRotH(mRot);
    } else {
        obj().model().modelRotCtrl().setRotH(50.0f);
        obj().model().modelRotCtrl().setRotV(mRot);
    }
}

void StateFireLv2::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.0001f), obj().param().common()._90);
}

void StateFireLv2::procFixPos() {
    MapCollResult result = obj().mapColl().result();
    if (mWait != 0) {
        mWait--;
        return;
    }
    if (mIsLanded) {
        hero::Utility::ChangeStateWaitOrFall(obj());
        return;
    }
    if (result.mIsHitFloor) {
        obj().move().resetSpeedH();
        mIsLanded = true;
        mWait = 10;
        mFrame = 0;
    }
}

}}}}  // namespace scn::step::hero::damage
