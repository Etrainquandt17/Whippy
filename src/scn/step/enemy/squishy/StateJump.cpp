#include "scn/step/enemy/squishy/StateJump.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
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
#include "scn/step/enemy/squishy/Custom.h"
#include "scn/step/enemy/squishy/ParamData.h"
#include "scn/step/enemy/squishy/StateLanding.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

StateJump::StateJump(Enemy* enemy)
    : StateBase(enemy), mFrame(0), mWaterFrame(0), mLandFrame(0), mIsFalling(false), mIsRising(false), mIsInWater(false) {
    const ParamData& param = obj().param().squishy();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.setJumpFromWater(false);
    mIsInWater = custom.isInWater(true);
    obj().model().reqScript(8);
    obj().model().anim().setFrameRate(obj().param().squishy().mJumpFrameRate);
    obj().move().resetVelocity();
    switch (obj().level()) {
    case 0:
        mLandFrame = param.mJumpLandFrame[0];
        break;
    case 1:
        mLandFrame = param.mJumpLandFrame[1];
        break;
    default:
        mLandFrame = param.mJumpLandFrame[2];
        break;
    }
}

StateJump::~StateJump() {}

void StateJump::procAnim() {
    const ParamData& param = obj().param().squishy();
    mFrame++;
    if (mFrame == param.mJumpStartFrame) {
        obj().model().reqScript(9);
        obj().model().anim().setFrameRate(param.mJumpFrameRate);
    }
    if (obj().move().velocity().y > 0.0f && !mIsInWater) {
        mIsRising = true;
    }
    if (obj().move().velocity().y < 0.0f && !mIsFalling) {
        obj().model().reqScript(1);
        mIsRising = false;
        mIsFalling = true;
    }
    if ((mIsRising || mIsFalling) && mIsInWater) {
        if (mIsFalling) {
            obj().move().resetSpeedH();
        }
        mWaterFrame++;
        if ((mIsRising && mWaterFrame == param.mJumpWaterFrame) || (mIsFalling && mWaterFrame == mLandFrame)) {
            obj().brainCtrl().toValid();
        }
    } else {
        mWaterFrame = 0;
    }
}

void StateJump::procMove() {
    const ParamData& param = obj().param().squishy();
    if (mFrame >= param.mJumpStartFrame) {
        if (mFrame == param.mJumpStartFrame) {
            if (obj().footState().isGround()) {
                obj().footState().setAir();
            }
            f32 speedH = obj().variation() == 0x9f ? 0.0f : param.mJumpSpeedH;
            f32 speedV = obj().variation() == 0x9f ? param.mJumpSpeedVStay : param.mJumpSpeedV;
            obj().move().setVelocity(hel::math::Vector3(speedH * obj().target().getSign(), speedV, 0.0f));
        }
        if (mIsInWater) {
            if (mIsRising) {
                obj().move().decel(param.mWaterDecel);
            } else {
                obj().move().airDecelFall(param.mAirDecel, param.mFallWater);
            }
        } else {
            obj().move().airDecelFall(param.mAirDecel, param.mFall);
        }
    }
}

void StateJump::procFixPos() {
    mIsInWater = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).isInWater(true);
    if (obj().mapColl().result().isHitWallFront()) {
        obj().move().setSpeedH(obj().move().velocity().x * -1.0f);
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    if (obj().mapColl().result().mIsHitFloor && mFrame > obj().param().squishy().mJumpStartFrame) {
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    }
}

}
}
}
}
