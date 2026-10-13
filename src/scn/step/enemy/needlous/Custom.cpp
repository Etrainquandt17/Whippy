#include "scn/step/enemy/needlous/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
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
#include "scn/step/enemy/needlous/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace needlous {

Custom::Custom(Enemy& enemy)
    : CustomBase(enemy), mSmokeFrame(0), mIsRunSE(false), mIsSEPlaying(false), mIsIdlingTurn(false), mIsAttack(false), mMoveCount(0),
      mMaxMoveCount(0), mSpeed(0.0f), mAttackSpeed(obj().param().needlous().mAttackAccel._0), mCurSpeed(0.0f) {
    const ParamData& param = obj().param().needlous();
    switch (enemy.level()) {
    case 0:
        mSpeed = 0.02f;
        break;
    case 1:
        mSpeed = 0.03f;
        break;
    case 2:
        mSpeed = 0.04f;
        break;
    default:
        mSpeed = 0.06f;
        break;
    }
    mCurSpeed = mSpeed;
    mMaxMoveCount = param.mMoveDist / mCurSpeed;
}

void Custom::updateMoveCount() {
    if (obj().footState().isGround()) {
        mMoveCount++;
    }
}

bool Custom::isMaxMoveCountOver() {
    return mMoveCount == mMaxMoveCount;
}

void Custom::resetMoveCount(bool isTurn) {
    const ParamData& param = obj().param().needlous();
    if (isTurn) {
        f32 current = mCurSpeed;
        f32 speed = mSpeed;
        if (current == speed) {
            speed = mAttackSpeed;
        }
        mMaxMoveCount = mCurSpeed / speed * static_cast<f32>(mMaxMoveCount - mMoveCount);
        if (mMaxMoveCount == 0) {
            mMaxMoveCount = 2.0f * param.mMoveDist / speed;
        }
        mCurSpeed = speed;
    } else {
        mMaxMoveCount = 2.0f * param.mMoveDist / mCurSpeed;
    }
    mMoveCount = 0;
}

void Custom::resetInitMoveCount() {
    mMaxMoveCount = obj().param().needlous().mMoveDist / mCurSpeed;
    mMoveCount = 0;
}

void Custom::onDead() {
    mSE.stop();
}

void Custom::onProcFixPos() {
    if (mSmokeFrame != 0) {
        mSmokeFrame--;
    }
    if (mIsRunSE && !mIsSEPlaying) {
        mSE.start(0x2bf);
        mIsSEPlaying = true;
    } else if (!mIsRunSE && mIsSEPlaying) {
        mSE.stop();
        mIsSEPlaying = false;
    }
    mIsRunSE = false;
}

void Custom::setIdlingTurn(bool isIdlingTurn) {
    mIsIdlingTurn = isIdlingTurn;
}

void Custom::setAttack(bool isAttack) {
    mIsAttack = isAttack;
}

void Custom::runSE() {
    mIsRunSE = true;
}

bool Custom::isIdlingTurn() {
    return mIsIdlingTurn;
}

bool Custom::isAttack() {
    return mIsAttack;
}

void Custom::smoke() {
    if (mSmokeFrame == 0) {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x124), 0);
        mSmokeFrame = obj().param().needlous().mSmokeFrame;
    }
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::needlous
