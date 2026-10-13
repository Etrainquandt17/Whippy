#include "scn/step/enemy/lanzer/Custom.h"

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
#include "scn/step/enemy/lanzer/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace lanzer {

Custom::Custom(Enemy& enemy)
    : CustomBase(enemy), mSpeed(0.0f), mAnimRate(0.0f), mLoopCount(0), mNowLoop(0), mBasePosX(0.0f), mTurnFlag(false), mDir(false) {
    const ParamData& param = obj().param().lanzer();
    switch (obj().level()) {
    case 0:
        mSpeed = param.mSpeed[0];
        mLoopCount = 1;
        break;
    case 1:
        mSpeed = param.mSpeed[1];
        mLoopCount = 1;
        break;
    default:
        mSpeed = param.mSpeed[2];
        mLoopCount = 1;
        break;
    }
    mAnimRate = mSpeed / 0.04f;
    mBasePosX = obj().location().pos().x;
    mNowLoop = mLoopCount;
    mDir = obj().target().isRightDir();
}

bool Custom::onInit() {
    switch (obj().variation()) {
    case 0x8a:
        obj().target().setIsRightDir(false);
        break;
    case 0x8b:
        obj().target().setIsRightDir(true);
        break;
    }
    return false;
}

bool Custom::onDamaged() {
    return onInit();
}

f32 Custom::getSpeed() const {
    return mSpeed;
}

f32 Custom::getAnimRate() const {
    return mAnimRate;
}

u32 Custom::getLoopCount() const {
    return mLoopCount;
}

u32 Custom::getNowLoop() const {
    return mNowLoop;
}

void Custom::resetNowLoop() {
    mNowLoop = 0;
}

void Custom::incNowLoop() {
    mNowLoop++;
}

void Custom::resetBasePosX() {
    mBasePosX = 0.0f;
}

void Custom::setBasePosX() {
    if (0.0f == mBasePosX) {
        mBasePosX = obj().location().pos().x;
    }
}

void Custom::setBasePosX(f32 x) {
    mBasePosX = x;
}

f32 Custom::getBasePosX() {
    return mBasePosX;
}

void Custom::setTurnFlag() {
    mTurnFlag = true;
}

void Custom::resetTurnFlag() {
    mTurnFlag = false;
}

bool Custom::getTurnFlag() {
    return mTurnFlag;
}

void Custom::setDir(bool dir) {
    mDir = dir;
}

bool Custom::getDir() {
    return mDir;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}
}
}
}
