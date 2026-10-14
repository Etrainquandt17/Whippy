#include "scn/step/enemy/aquarock/Custom.h"

#include "hel/math/Matrix34.h"
#include "scn/step/chara/CliffChecker.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/aquarock/ParamData.h"
#include "snd/SERequestor.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace aquarock {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mRadius(0.0f), mCircumference(0.0f), mSpeed(0.0f), mAngleSpeed(0.0f) {
    switch (obj().variation()) {
    case 0xB1:
    case 0xC3:
    case 0xE2:
    case 0xE5:
        mRadius = obj().param().aquarock().mDiameterSmall;
        break;
    case 0xB2:
    case 0xC4:
    case 0xE3:
    case 0xE6:
        mRadius = obj().param().aquarock().mDiameterMiddle;
        break;
    default:
        mRadius = obj().param().aquarock().mDiameterLarge;
        break;
    }
    switch (obj().level()) {
    case 0:
        mSpeed = obj().param().aquarock().mSpeedLevel0;
        break;
    case 1:
        mSpeed = obj().param().aquarock().mSpeedLevel1;
        break;
    default:
        mSpeed = obj().param().aquarock().mSpeedLevel2;
        break;
    }
    obj().model().setCustomMtx(Matrix34::CreateScale(Vector3(mRadius, mRadius, mRadius)));
    mCircumference = 3.1415927f * mRadius;
    mRadius *= 0.5f;
    mAngleSpeed = 360.0f / (mCircumference / mSpeed) * obj().param().aquarock().mAngleSpeedRate;
    obj().culling().setValid(false);
    Vector3 pos = obj().location().pos();
    pos.y -= mRadius;
    obj().location().setPos(pos);
    obj().cliffChecker().setValid(false);
    obj().shadow().setVisibility(false);
}

bool Custom::onInWater() {
    obj().soundSE().start(0x2F6);
    return false;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

f32 Custom::getRadius() const {
    return mRadius;
}

f32 Custom::getSpeed() const {
    return mSpeed;
}

f32 Custom::getAngleSpeed() const {
    return mAngleSpeed;
}

}}}}  // namespace scn::step::enemy::aquarock
