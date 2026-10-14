#include "scn/step/enemy/babut/StateFlySinCurve.h"

#include "gobj/FootState.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/babut/Custom.h"
#include "scn/step/enemy/babut/ParamData.h"
#include "scn/step/enemy/babut/StateAttack.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace babut {

StateFlySinCurve::StateFlySinCurve(Enemy* enemy)
    : StateBase(enemy)
    , mAngle(180.0f)
    , mBaseY(enemy->location().pos().y)
    , mSpeedX(speedX() * obj().target().getSign())
    , mFrame(0) {
    if (obj().variation() != 0x4c) {
        f32 x = obj().location().pos().x;
        obj().target().setIsRightDir(Utility::GetNearestPlayerPos(obj()).x > x);
    }
    obj().footState().setAir();
    obj().model().reqScript(4);
}

void StateFlySinCurve::procMove() {
    const ParamData& param = obj().param().babut();
    mAngle += freq();
    if (mAngle >= 360.0f) {
        mAngle -= 360.0f;
    }
    if (mFrame < param.mSinCurveDescendFrame) {
        mFrame++;
        mBaseY -= param.mSinCurveDescendHeight / param.mSinCurveDescendFrame;
    }
    f32 offsetY = param.mSinCurveHeight * Math::SinDegF(mAngle);
    Vector3 pos = obj().location().pos();
    pos.y = mBaseY + offsetY;
    pos.x += mSpeedX;
    obj().location().setPos(pos);
    obj().objColl().clearSearchHit();
    obj().objColl().addSearchHit(0, param.mSearchRadius, Vector2(mSpeedX, param.mSearchOffsetY));
}

void StateFlySinCurve::procFixPos() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).startWingSound();
    if (obj().mapColl().result()._2 || Utility::ChkNururiByDir(obj(), 0.0f)) {
        mSpeedX = -mSpeedX;
        obj().target().setIsRightDir(mSpeedX >= 0.0f);
    } else if (obj().mapColl().result().mIsHitRoof) {
        mAngle = 90.0f;
        mBaseY = obj().location().pos().y - obj().param().babut().mSinCurveHeight;
    } else if (obj().mapColl().result().mIsHitFloor) {
        mAngle = 270.0f;
        mBaseY = obj().location().pos().y + obj().param().babut().mSinCurveHeight;
    }
}

void StateFlySinCurve::procObjCollReact() {
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).chkCaptureHero()) {
        obj().soundSE().start(0x309);
        obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
    }
}

f32 StateFlySinCurve::difficultyRate() const {
    const ParamData& param = obj().param().babut();
    switch (static_cast<u32>(obj().level())) {
    case 0:
        return param.mDifficultyRateLv0;
    case 1:
        return param.mDifficultyRateLv1;
    default:
        return param.mDifficultyRateLv2;
    }
}

f32 StateFlySinCurve::freq() const {
    return obj().param().babut().mSinCurveFreq * difficultyRate();
}

f32 StateFlySinCurve::speedX() const {
    return obj().param().babut().mSinCurveSpeedX * difficultyRate();
}

}}}}  // namespace scn::step::enemy::babut
