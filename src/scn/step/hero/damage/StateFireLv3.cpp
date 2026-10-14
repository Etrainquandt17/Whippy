#include "scn/step/hero/damage/StateFireLv3.h"
#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/DamageFlash.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFaint.h"
#include "scn/step/hero/damage/Utility.h"
#include "util/StateChanger.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace hero {
namespace damage {

StateFireLv3::StateFireLv3(Hero* hero)
    : StateBase(hero)
    , mRot(0.0f)
    , mIsLanded(false)
    , mWait(20)
    , mFrame(0) {
    obj().footState().setAir();
    obj().model().script().start(0x4A);
    hero::Utility::ReqNakigoe(obj());
    Utility::InitTarget(obj());
    Utility::InitVelocity(obj());
    obj().invincible().setPerm();
    obj().effect()._58.requestN(static_cast<effect::Kind>(0xDB), 1);
    obj().damageFlash().set(static_cast<ocoll::Element>(2));
}

StateFireLv3::~StateFireLv3() {
    obj().model().modelRotCtrl().setRotV(0.0f);
    obj().model().modelRotCtrl().setRotH(0.0f);
    obj().damageFlash().unset();
    obj().invincible().set(120);
}

void StateFireLv3::procAnim() {
    if (++mFrame >= 60) {
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

void StateFireLv3::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.0001f), obj().param().common()._90);
}

void StateFireLv3::procFixPos() {
    MapCollResult result = obj().mapColl().result();
    Utility::ReflectWallL(obj());
    if (mWait != 0) {
        mWait--;
        return;
    }
    if (mIsLanded) {
        if (obj().mapColl().result().mIsHitFloor) {
            obj().move().resetVelocity();
            obj().stateChanger().setNextState<common::StateFaint, Hero*, u32>(objPtr(), 2);
        }
        return;
    }
    if (result.mIsHitFloor) {
        obj().move().resetSpeedH();
        mIsLanded = true;
        mWait = 20;
        mFrame = 0;
    }
}

}}}}  // namespace scn::step::hero::damage
