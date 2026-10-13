#include "scn/step/boss/kingsdoo/StateJumpMachinegun.h"

#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/common/StateLanding.h"
#include "scn/step/boss/kingsdoo/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace boss {
namespace kingsdoo {

StateJumpMachinegun::StateJumpMachinegun(Boss* boss) :StateBase(boss), mCount(0), mStartPos(), mRotV(0.0f), mIsSwing(false) {
    obj().footState().setAir();
    obj().model().reqScript(16);
    mStartPos = obj().location().pos().getXY();
}

StateJumpMachinegun::~StateJumpMachinegun() {
    obj().model().rotCtrl().initRotV(0.0f);
}

void StateJumpMachinegun::procAnim() {
    const Param& param = obj().param().kingsdoo();
    if (obj().scriptTrigger().get(0)) {
        reqMachinegun();
    }
    if (obj().scriptTrigger().get(1)) {
        mIsSwing = !mIsSwing;
    }
    if (mCount < param.mJumpMachinegunTime) {
        mCount++;
        return;
    }
    obj().stateChanger().setNextState<common::StateLanding, Boss*>(objPtr());
}

void StateJumpMachinegun::procMove() {
    const Param& param = obj().param().kingsdoo();
    f32 height;
    f32 rate = static_cast<f32>(mCount) / static_cast<f32>(param.mJumpMachinegunTime);
    height = 1.0f - (1.0f - hel::math::Math::SinDegF(180.0f * rate)) *
                            ((1.0f - hel::math::Math::SinDegF(180.0f * rate)) * (1.0f - hel::math::Math::SinDegF(180.0f * rate)));
    hel::math::Vector2 pos = mStartPos;
    pos.y += height * param.mJumpMachinegunHeight;
    obj().location().setPos(pos.toVector3());
}

void StateJumpMachinegun::procFixPos() {
    const Param& param = obj().param().kingsdoo();
    if (obj().target().isRightDir()) {
        if (mIsSwing) {
            if (mRotV > -param.mMachinegunRotMax) {
                mRotV -= param.mMachinegunRotSpeed;
            }
        } else {
            if (mRotV < 0.0f) {
                mRotV += param.mMachinegunRotSpeed;
            }
        }
    } else {
        if (mIsSwing) {
            if (mRotV < param.mMachinegunRotMax) {
                mRotV += param.mMachinegunRotSpeed;
            }
        } else {
            if (mRotV > 0.0f) {
                mRotV -= param.mMachinegunRotSpeed;
            }
        }
    }
    obj().model().rotCtrl().initRotV(mRotV);
}

void StateJumpMachinegun::reqMachinegun() {
    const Param& param = obj().param().kingsdoo();
    hel::math::Vector2 pos = obj().location().pos().getXY();
    pos += hel::math::Vector2(param.mMachinegunOffset.x * obj().target().getSign(), param.mMachinegunOffset.y);
    hel::math::Vector2 dir = hel::math::Vector2::BASIS_Y * -1.0f;
    f32 angle = app::Random::RandF32(param.mMachinegunAngleMin, param.mMachinegunAngleMax) * obj().target().getSign();
    dir.rotate(0.017453292f * angle);
    weapon::Desc desc(static_cast<weapon::Kind>(0x32), 2, static_cast<ostop::Flag>(8), pos, dir, obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
}

}
}
}
}
