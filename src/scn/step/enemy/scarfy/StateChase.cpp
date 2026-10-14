#include "scn/step/enemy/scarfy/StateChase.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/scarfy/ParamData.h"

using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

StateChase::StateChase(Enemy* enemy) : StateBase(enemy), _8(0), mSpd(0.0f), mSpdLimit(0.0f), mVelocity() {
    obj().footState().setAir();
    obj().model().reqScript(0);
    obj().brainCtrl().toValid();
    mSpd = getSpd();
    mSpdLimit = getSpdLimit();
}

StateChase::~StateChase() {}

void StateChase::procAnim() {
    Utility::TurnHero(obj());
}

void StateChase::procMove() {
    Vector3 pos = obj().location().pos();
    Vector3 target = Utility::GetNearestPlayerPos(obj()).toVector3();
    target.y += obj().param().scarfy().mChaseTargetOffsetY;
    Vector3 dir = target - pos;
    Vector3 accel = Vector3::ZERO;
    if (dir.isZeroLoose(0.00001f)) {
        dir = Vector3::ZERO;
    } else {
        dir.normalize();
    }
    accel.x = mSpd * dir.x;
    accel.y = mSpd * dir.y;
    Vector3 nururi = obj().nururi().getNururiDir().toVector3();
    if (mVelocity.dot(nururi) < 0.0f) {
        if (Math::Abs(nururi.x) <= 0.5f) {
            mVelocity.x = nururi.y >= 0.0f ? -mSpdLimit : mSpdLimit;
        } else {
            mVelocity.x *= -1.0f;
        }
        mVelocity.y = mVelocity.y >= 0.0f ? -getSpdLimit() : getSpdLimit();
        mVelocity.y *= 0.2f;
        mSpdLimit = getSpdLimit() / 2.0f;
    } else {
        mSpdLimit = getSpdLimit();
    }
    mVelocity += accel;
    if (mVelocity.x > mSpdLimit) {
        mVelocity.x = mSpdLimit;
    } else if (mVelocity.x < -mSpdLimit) {
        mVelocity.x = -mSpdLimit;
    }
    if (mVelocity.y > mSpdLimit) {
        mVelocity.y = mSpdLimit;
    } else if (mVelocity.y < -mSpdLimit) {
        mVelocity.y = -mSpdLimit;
    }
    obj().move().setVelocity(mVelocity);
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Zero());
}

f32 StateChase::getSpdLimit() {
    const ParamData& param = obj().param().scarfy();
    switch (static_cast<u32>(obj().level())) {
    case 0:
        return param.mLevel[0].mSpdLimit;
    case 1:
        return param.mLevel[1].mSpdLimit;
    case 2:
        return param.mLevel[2].mSpdLimit;
    case 3:
        return param.mLevel[3].mSpdLimit;
    default:
        return param.mLevel[4].mSpdLimit;
    }
}

f32 StateChase::getSpd() {
    const ParamData& param = obj().param().scarfy();
    switch (static_cast<u32>(obj().level())) {
    case 0:
        return param.mLevel[0].mSpd;
    case 1:
        return param.mLevel[1].mSpd;
    case 2:
        return param.mLevel[2].mSpd;
    case 3:
        return param.mLevel[3].mSpd;
    default:
        return param.mLevel[4].mSpd;
    }
}

}}}}  // namespace scn::step::enemy::scarfy
