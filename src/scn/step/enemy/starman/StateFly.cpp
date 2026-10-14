#include "scn/step/enemy/starman/StateFly.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/detail/ShapeDiamondContext.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/starman/ParamData.h"
#include "scn/step/enemy/starman/StateFall.h"
#include "snd/SERequestor.h"

using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace starman {

StateFly::StateFly(Enemy* enemy) : StateBase(enemy), mAngle(0.0f), mFrame(0), mRise(0.0f) {
    const ParamData& param = obj().param().starman();
    switch (obj().level()) {
    case 0:
        mAccel = param.mFlyAccel[0];
        break;
    case 1:
        mAccel = param.mFlyAccel[1];
        break;
    default:
        mAccel = param.mFlyAccel[2];
        break;
    }
    f32 x = obj().location().pos().x;
    mPrevX = x;
    mCurX = x;
    obj().footState().setAir();
    obj().move().resetSpeedH();
    obj().model().reqScript(10);
    if (obj().variation() == 0x5e) {
        mIsStraight = true;
    } else {
        mIsStraight = false;
    }
    obj().mapColl().changeActorShape(mcoll::detail::ShapeDiamondContext::CreateBaseCenter(0.4f, 0.49f, 0.5f));
}

StateFly::~StateFly() {
    obj().mapColl().changeActorShape(mcoll::detail::ShapeDiamondContext::CreateBaseBottom(0.4f, 0.49f, 0.5f));
}

void StateFly::procAnim() {
    mFrame++;
    if (mFrame > obj().param().starman().mFlyFrame && mIsStraight) {
        obj().move().resetSpeedH();
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

void StateFly::procMove() {
    if (!mIsStraight) {
        flySinCurve();
    } else {
        flyStraight();
    }
    mCurX = obj().location().pos().x;
    f32 diff = Math::AbsF32(mCurX - mPrevX);
    if (diff < obj().param().starman().mFlyStopDist) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    mPrevX = mCurX;
}

void StateFly::procFixPos() {
    if (obj().mapColl().result().isHitWallFront()) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    if (obj().mapColl().result().mIsHitRoof) {
        obj().move().resetSpeedH();
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

void StateFly::flySinCurve() {
    const ParamData& param = obj().param().starman();
    obj().move().groundAccel(obj().target().isRightDir(), mAccel);
    Vector3 pos = obj().location().pos();
    f32 offset = param.mFlySinWidth * Math::CosDegF(mAngle);
    pos.y += offset;
    obj().location().setPos(pos);
    mAngle += param.mFlySinSpeed;
    if (mAngle >= 360.0f) {
        mAngle = 0.0f;
    }
}

void StateFly::flyStraight() {
    const ParamData& param = obj().param().starman();
    obj().move().groundAccel(obj().target().isRightDir(), param.mFlyAccel[2]);
    Vector3 pos = obj().location().pos();
    pos.y += param.mStraightSpeedY;
    if (mFrame <= param.mStraightStartFrame) {
        pos.y += param.mStraightStartY;
        pos.x += param.mStraightStartX;
    }
    if (mFrame >= param.mStraightRiseFrame) {
        mRise += param.mStraightRiseAccel;
        if (mRise >= param.mStraightRiseMax) {
            mRise = param.mStraightRiseMax;
        }
        pos.y += mRise;
    }
    obj().location().setPos(pos);
}

}}}}  // namespace scn::step::enemy::starman
