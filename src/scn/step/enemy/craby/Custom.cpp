#include "scn/step/enemy/craby/Custom.h"

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
#include "scn/step/enemy/craby/ParamData.h"
#include "snd/SERequestor.h"

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

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
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
