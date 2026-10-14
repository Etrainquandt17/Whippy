#include "scn/step/boss/roah/StateBullet.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/mahoroaroah/Custom.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Direction3;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateBullet::StateBullet(Boss* boss, Config config)
    : StateBase(boss), mCount(0), mBasePos(), mIsMove(false), mIsRequest(false), mConfig(config) {
    const Param& param = obj().param().roah();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mBasePos = obj().location().pos().getXY();
    obj().model().reqScript(22);
    custom.mahoroaCtrl().getCustom().reqMotionBullet(mConfig._4);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Vector3 pos = obj().location().pos() + Vector2(param.mBulletEffectOffset).toVector3();
    Direction3 dir;
    dir.mUp = Vector3::BASIS_X;
    dir.restructUpFront();
    dir.restructUpLeft();
    switch (mConfig._0) {
    case 3:
        obj().effect().normal().requestPD(static_cast<effect::Kind>(0x4C6), pos, dir);
        break;
    case 4:
        obj().effect().normal().requestPD(static_cast<effect::Kind>(0x4C4), pos, dir);
        break;
    case 5:
        obj().effect().normal().requestPD(static_cast<effect::Kind>(0x4C8), pos, dir);
        break;
    case 6:
        obj().effect().normal().requestPD(static_cast<effect::Kind>(0x4C6), pos, dir);
        obj().effect().normal().requestPD(static_cast<effect::Kind>(0x4C4), pos, dir);
        break;
    }
    Utility::ControlHateOnAction(obj());
}

StateBullet::~StateBullet() {}

void StateBullet::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mCount++;
    if (obj().scriptTrigger().get(0)) {
        mIsRequest = true;
    }
    if (mIsRequest) {
        if (!custom.weaponCtrl().isReqBuffEmpty()) {
            custom.weaponCtrl().requestOneByOne();
        }
    }
    if (obj().scriptTrigger().get(1)) {
        mIsMove = true;
        mCount = 0;
    }
    if (obj().scriptTrigger().get(2)) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateBullet::procMove() {
    const Param& param = obj().param().roah();
    if (mIsMove) {
        f32 t = static_cast<f32>(mCount) / static_cast<f32>(param.mOarMoveFrame);
        f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);
        Vector2 pos = mBasePos;
        pos.x -= param.mOarMoveDistance * Math::SinDegF(180.0f * rate);
        obj().location().setPos(pos.toVector3());
        if (mCount == param.mOarMoveFrame) {
            mIsMove = false;
        }
    }
}

void StateBullet::procFixPos() {}

}}}}  // namespace scn::step::boss::roah
