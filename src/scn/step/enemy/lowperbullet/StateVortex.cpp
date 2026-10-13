#include "scn/step/enemy/lowperbullet/StateVortex.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/Water.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/lowperbullet/Custom.h"
#include "scn/step/enemy/lowperbullet/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace lowperbullet {

StateVortex::StateVortex(Enemy* enemy)
    : StateBase(enemy), mFrame(0), mShakeFrame(0), mCenter(enemy->location().pos()), mOffset(), mVelocity() {
    obj().mapColl().setValid(false);
    obj().objColl().bodyColl().setStateXlu();
    obj().vacuumReceiver().setIsValid(false);
    obj().model().reqScript(0);
}

StateVortex::~StateVortex() {
    obj().vacuumReceiver().setIsValid(true);
    obj().objColl().bodyColl().setStateNormal();
    obj().mapColl().setValid(true);
}

void StateVortex::procAnim() {
    if (mFrame == 0) {
        mVelocity = obj().move().velocity();
        obj().move().resetVelocity();
    }
    if (mFrame < 60) {
        mFrame++;
        if (mFrame == 60) {
            obj().objColl().bodyColl().setStateNormal();
            obj().vacuumReceiver().setIsValid(true);
        }
    } else if (mShakeFrame < 90) {
        mShakeFrame++;
        if (mShakeFrame == 60) {
            obj().model().shake().request(static_cast<chara::ShakeKind>(3));
        }
        if (mShakeFrame == 70) {
            obj().model().shake().request(static_cast<chara::ShakeKind>(4));
        }
    } else {
        hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).requestWeaponBurst();
        obj().deadWithEffect();
    }
}

void StateVortex::procMove() {
    f32 rate = static_cast<f32>(mFrame) / 60.0f;
    mOffset += mVelocity * (1.0f - rate);
    hel::math::Vector3 pos = mOffset;
    hel::math::Vector3 axis = hel::math::Vector3::BASIS_Y;
    axis.rotate(hel::math::Vector3::AXIS_X, 0.34906584f);
    f32 angle = 1080.0f * hel::math::Math::SinDegF(90.0f * rate);
    pos.rotate(axis, 0.017453292f * angle);
    pos.z *= 6.0f;
    pos += mCenter;
    obj().location().setPos(pos);
}

void StateVortex::procFixPos() {}

}}}}  // namespace scn::step::enemy::lowperbullet
