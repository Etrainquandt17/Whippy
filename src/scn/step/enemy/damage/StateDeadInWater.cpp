#include "scn/step/enemy/damage/StateDeadInWater.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/ColorF.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Water.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Flash.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/ObjCollReact.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "snd/SERequestor.h"
#include "std/min.h"

namespace scn {
namespace step {
namespace enemy {
namespace damage {

StateDeadInWater::StateDeadInWater(Enemy* enemy)
    : StateBase(enemy)
    , mFrame(0)
    , mIsSink(true)
    , mFrameRate(enemy->model().anim().frameRate())
    , mFlashAngle(0.0f)
    , mFlashSpeed(0.0f)
    , mFlashRate(1.0f) {
    obj().footState().setAir();
    if (obj().move().velocity().y > 0.0f) {
        obj().move().setVelocity(hel::math::Vector3(0.0f, 0.02f, 0.0f));
        mIsSink = false;
    } else if (obj().mapColl().floorNormal().x != 0.0f) {
        obj().move().setVelocity(hel::math::Vector3(0.0f, -0.02f, 0.0f));
        mFrameRate = 0.8f;
        mIsSink = false;
    } else {
        obj().move().setVelocity(hel::math::Vector3(0.0f, -0.03f, 0.0f));
    }
    obj().vacuumReceiver().setIsValid(false);
    obj().nururi().setCanNururi(false);
    obj().nururi().setValid(false);
    obj().model().reqScript(6);
    obj().objColl().bodyColl().setStateXlu();
    obj().objCollReact().setDamageState();
    obj().water().setForbidEffect(true);
    obj().water().setUseCallback(false);
    obj().soundSE().start(0x2f6);
}

StateDeadInWater::~StateDeadInWater() {}

void StateDeadInWater::procAnim() {
    mFrame++;
    deadFlash();
    if ((mFrame == 30 || mFrame == 60) && mIsSink) {
        f32 scale = enemy::Utility::GetModelScaleBySizeType(obj());
        hel::math::Vector3 pos = obj().location().centerPos() - hel::math::Vector3(0.0f, 0.45f, 0.0f) * scale;
        obj().effect().normal().requestP(static_cast<effect::Kind>(0x133), pos, scale);
    }
    if (5 < mFrame && mFrame <= 30) {
        mFrameRate -= 0.02f;
    } else if (mFrame > 30) {
        mFrameRate -= 0.01f;
    }
    if (mFrameRate < 0.1f) {
        mFrameRate = 0.1f;
    }
    obj().model().anim().setFrameRate(mFrameRate);
    if (mFrame >= 90 || !obj().water().isInWater()) {
        obj().deadWithEffectNoItem();
    }
}

void StateDeadInWater::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Create(0.0003f));
}

void StateDeadInWater::procFixPos() {}

void StateDeadInWater::deadFlash() {
    mFlashSpeed = std::min(3.5f + mFlashSpeed, 90.0f);
    mFlashAngle += mFlashSpeed;
    while (360.0f <= mFlashAngle) {
        mFlashAngle -= 360.0f;
    }
    mFlashRate = 0.95f * mFlashRate + 0.0375f;
    f32 rate = mFlashRate * (0.5f * (1.0f + hel::math::Math::CosDegF(mFlashAngle)));
    u32 alpha = 255.0f * rate;
    obj().flash().setEnf1F(hel::common::ColorF(192.0f, 180.0f, 180.0f, alpha).toGXColor());
}

}}}}  // namespace scn::step::enemy::damage
