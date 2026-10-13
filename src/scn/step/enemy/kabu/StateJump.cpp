#include "scn/step/enemy/kabu/StateJump.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/kabu/ParamData.h"
#include "scn/step/enemy/kabu/StateTeleport.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy), mFrame(0), mIsRight(false), mSpeedH(0.0f) {
    obj().footState().setGround();
    obj().model().reqScript(7);
}

StateJump::~StateJump() {}

void StateJump::procAnim() {
    const ParamData& param = obj().param().kabu();
    u32 index = obj().model().anim().currentG3DAnimIndex();
    if (obj().model().isAllEnd()) {
        if (index == 6) {
            obj().model().reqScript(8);
        } else if (index == 7) {
            if (obj().variation() != 0x68) {
                obj().model().reqScript(1);
                obj().model().anim().setFrameRate(param.mJumpFallFrameRate);
            } else {
                obj().move().resetSpeedV();
                obj().stateChanger().setNextState<StateTeleport, Enemy*>(objPtr());
            }
        }
    }
}

void StateJump::procMove() {
    const ParamData& param = obj().param().kabu();
    mFrame++;
    if (mFrame >= param.mJumpStartFrame) {
        if (obj().footState().isGround()) {
            obj().footState().setAir();
            setSpeed();
            hel::math::Vector3 velocity = obj().move().velocity();
            mSpeedH = velocity.x;
        }
        const common::ParamData& common = obj().param().common();
        const gobj::MoveParamAccel& accel = gobj::MoveParamAccel::Create(mSpeedH, mSpeedH, 0.0f);
        obj().move().airAccelFall(mIsRight, accel, common.mFall);
    }
}

void StateJump::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor && mFrame > obj().param().kabu().mJumpStartFrame) {
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    } else if (!obj().mapColl().result().mIsHitFloor && obj().footState().isGround()) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

void StateJump::setSpeed() {
    const ParamData& param = obj().param().kabu();
    int type = app::Random::Rand(4);
    if (obj().variation() == 0x68) {
        type = 1;
    }
    f32 speedV;
    f32 speedH;
    switch (type) {
    case 0:
        speedV = param.mJumpSpeedVStay;
        speedH = 0.0f;
        mIsRight = obj().target().isRightDir();
        break;
    case 1:
        speedV = param.mJumpSpeedVHigh;
        speedH = 0.0f;
        mIsRight = obj().target().isRightDir();
        break;
    case 2:
        speedV = param.mJumpSpeedV;
        speedH = param.mJumpSpeedH;
        mIsRight = true;
        break;
    case 3:
        speedV = param.mJumpSpeedV;
        speedH = obj().param().kabu().mJumpSpeedH;
        mIsRight = false;
        break;
    default:
        speedV = param.mJumpSpeedV;
        speedH = 0.0f;
        break;
    }
    obj().move().setSpeedV(speedV);
    obj().move().setSpeedH(speedH);
}

}
}
}
}
