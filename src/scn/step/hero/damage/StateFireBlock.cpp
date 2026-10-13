#include "scn/step/hero/damage/StateFireBlock.h"
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

namespace scn {
namespace step {
namespace hero {
namespace damage {

StateFireBlock::StateFireBlock(Hero* hero)
    : StateBase(hero)
    , mRot(0.0f)
    , mIsLanded(false)
    , mWait(20)
    , mFrame(0) {
    obj().footState().setAir();
    obj().model().script().start(0x49);
    obj().comp().permEffect().powerful().requestP(static_cast<effect::Kind>(0xD9),
                                                  obj().location().pos() + hel::math::Vector3(0.0f, 0.5f, 0.0f));
    hel::math::Vector3 velocity = hel::math::Vector3::BASIS_X;
    f32 angle = 60.0f;
    angle += 10.0f * app::Random::RandAF();
    velocity.rotate(hel::math::Vector3::BASIS_Z, 0.017453292f * angle);
    velocity.x *= -1.0f * obj().target().getSign();
    velocity *= 0.125f;
    obj().move().setVelocity(velocity);
    obj().invincible().setPerm();
    obj().effect()._58.requestN(static_cast<effect::Kind>(0xDB), 1);
    obj().damageFlash().set(static_cast<ocoll::Element>(2));
    obj().soundSE()._4.start(0x29F);
}

StateFireBlock::~StateFireBlock() {
    obj().model().modelRotCtrl().setRotV(0.0f);
    obj().model().modelRotCtrl().setRotH(0.0f);
    obj().damageFlash().unset();
    obj().invincible().set(120);
}

void StateFireBlock::procAnim() {
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
        hel::math::Vector2 dir = obj().move().velocity().getXY();
        if (!dir.isZero()) {
            dir.normalize();
            f32 angle = hel::math::Vector2::BASIS_Y.signedAngle(dir);
            obj().model().modelRotCtrl().setRotV(57.29578f * angle);
        }
        obj().model().modelRotCtrl().setRotH(mRot);
    } else {
        obj().model().modelRotCtrl().setRotH(50.0f);
        obj().model().modelRotCtrl().setRotV(mRot);
    }
}

void StateFireBlock::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.0001f), obj().param().common()._90);
}

void StateFireBlock::procFixPos() {
    MapCollResult result = obj().mapColl().result();
    Utility::ReflectWallS(obj());
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
