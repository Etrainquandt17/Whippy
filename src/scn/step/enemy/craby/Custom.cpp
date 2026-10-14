#include "scn/step/enemy/craby/Custom.h"

#include "scn/step/chara/Location.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/craby/ParamData.h"
#include "snd/SERequestor.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace craby {

Custom::Custom(Enemy& enemy)
    : CustomBase(enemy), mCounter(obj().param().craby().mAimWaitFrame), mIsAimValid(true), mIsAttackValid(false),
      mBasePosX(obj().location().pos().x) {}

bool Custom::onDamaged() {
    reset();
    return false;
}

bool Custom::onInWater() {
    obj().soundSE().start(0x2F6);
    return false;
}

bool Custom::onOutWater() {
    return onInWater();
}

bool Custom::isPlayerInAimArea() {
    const ParamData& param = obj().param().craby();
    if (mIsAimValid) {
        mCounter.reset();
        return Utility::IsHeroInRange(obj(), param.mAimRangeH, 0.0f, -param.mAimRangeV, param.mAimRangeV);
    }
    mCounter.advance();
    if (mCounter.isEnd()) {
        mCounter.reset();
        mIsAimValid = true;
    }
    return false;
}

void Custom::reset() {
    mCounter.reset();
    mIsAimValid = true;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

void Custom::setAttackValid(bool isValid) {
    mIsAttackValid = isValid;
}

void Custom::setBasePosX(f32 x) {
    mBasePosX = x;
}

f32 Custom::getBasePosX() {
    return mBasePosX;
}

}}}}  // namespace scn::step::enemy::craby
