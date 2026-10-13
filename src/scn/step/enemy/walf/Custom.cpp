#include "scn/step/enemy/walf/Custom.h"

#include "app/Random.h"
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
#include "scn/step/chara/Water.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/walf/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace walf {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mDirBeforeJump(false), mIsDamaged(true), mJumpCount(0), mJumpRand(1) {
    mTurnStep = static_cast<int>(obj().target().getSign()) * 2;
}

bool Custom::onDamaged() {
    mIsDamaged = true;
    mTurnStep = static_cast<int>(obj().target().getSign()) * 2;
    return false;
}

bool Custom::onInWater() {
    obj().soundSE().start(0x2F6);
    return false;
}

bool Custom::onOutWater() {
    return onInWater();
}

bool Custom::isInWater() {
    return obj().water().isPosInWater(obj().param().walf().mInWaterOffset);
}

bool Custom::isFloating(hel::math::Vector2 offset) {
    if (!obj().water().isPosInWater(obj().param().walf().mInWaterOffset + offset) &&
        obj().water().isPosInWater(obj().param().walf().mFloatingOffset + offset)) {
        return true;
    }
    return false;
}

bool Custom::isFloating() {
    if (!obj().water().isPosInWater(obj().param().walf().mInWaterOffset) &&
        obj().water().isPosInWater(obj().param().walf().mFloatingOffset)) {
        return true;
    }
    return false;
}

bool Custom::checkTurn(bool isRight) {
    if (isRight == obj().target().isRightDir()) {
        if (hel::math::Math::Abs(mTurnStep) == 2) {
            mTurnStep = static_cast<int>(obj().target().getSign()) * -1;
            return true;
        } else {
            mTurnStep = static_cast<int>(obj().target().getSign()) * 2;
            return false;
        }
    } else {
        if (hel::math::Math::Abs(mTurnStep) == 2) {
            mTurnStep = static_cast<int>(obj().target().getSign()) * -1;
            return false;
        } else {
            mTurnStep = -(static_cast<int>(obj().target().getSign()) * 2);
            return false;
        }
    }
}

bool Custom::checkJump() {
    s32 rand = app::Random::Rand(3);
    bool wasJump = true;
    if (mJumpRand == 0) {
        wasJump = false;
    }
    mJumpRand = rand;
    if (rand == 0) {
        if (!wasJump) {
            mJumpCount++;
            return false;
        } else {
            mJumpCount = 0;
            return true;
        }
    } else {
        mJumpCount++;
        if (mJumpCount >= 2) {
            mJumpCount = 0;
            return true;
        }
        return false;
    }
}

void Custom::setDirBeforeJump(bool isRight) {
    mDirBeforeJump = isRight;
}

bool Custom::checkTurnAfterJump() {
    if (mIsDamaged) {
        mIsDamaged = false;
        return false;
    }
    return checkTurn(mDirBeforeJump);
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::walf
