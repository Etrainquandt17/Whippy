#include "scn/step/boss/roah/StateOar.h"

#include "gobj/GearModel.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/mahoroaroah/Custom.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/core/PermEffect.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateOar::StateOar(Boss* boss) : StateBase(boss), mCount(0), mBasePos(), mIsMove(false), mIsOarLost(false), mIsRequest(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mBasePos = obj().location().pos().getXY();
    custom.resetSubAnimOar();
    obj().model().reqScript(19);
    custom.mahoroaCtrl().getCustom().reqMotionOar();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Utility::ControlHateOnAction(obj());
}

StateOar::~StateOar() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setSubAnimOar();
    if (!mIsOarLost) {
        for (u32 i = 0; i < 6; i++) {
            Vector3 pos = obj().model().model().nodes().at(i + 13).worldTrans();
            obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x7A), pos);
        }
    }
}

void StateOar::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mCount++;
    if (obj().scriptTrigger().get(0)) {
        mIsRequest = true;
    }
    if (mIsRequest) {
        if (!custom.weaponCtrl().isReqBuffEmpty()) {
            custom.weaponCtrl().requestOneByOne();
        }
        if (custom.weaponCtrl().isReqBuffEmpty()) {
            obj().model().model().nodes().at(12).setVisibilityBelow(false);
            mIsOarLost = true;
            mIsRequest = false;
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

void StateOar::procMove() {
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

void StateOar::procFixPos() {}

}}}}  // namespace scn::step::boss::roah
