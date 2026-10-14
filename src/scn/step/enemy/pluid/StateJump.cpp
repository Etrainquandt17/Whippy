#include "scn/step/enemy/pluid/StateJump.h"

#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/pluid/Custom.h"
#include "scn/step/enemy/pluid/ParamData.h"

using app::Random;
using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

StateJump::StateJump(Enemy* enemy)
    : StateBase(enemy), mIsStart(true), mIsJumped(false), mIsRight(false), mFrame(0), mSpeedH(0.0f), mSpeedV(0.0f) {
    obj().footState().setGround();
    obj().model().reqScript(7);
    f32 rate = 1.0f;
    mSpeedV = obj().param().pluid().mJumpSpeedV;
    if (Random::Rand(4) == 3) {
        rate = obj().param().pluid().mHighJumpRate;
        mSpeedV = obj().param().pluid().mHighJumpSpeedV;
    }
    int num = DynamicCastToRef<Custom, ICustom>(obj().custom()).setJumpNum();
    switch (num) {
    case 0:
        mSpeedH = 0.0f;
        mSpeedV *= rate;
        break;
    case 1:
        mSpeedH = rate * obj().param().pluid().mJumpSpeedH;
        mSpeedV *= rate;
        mIsRight = false;
        break;
    case 2:
        mSpeedH = rate * obj().param().pluid().mJumpSpeedH;
        mSpeedV *= rate;
        mIsRight = true;
        break;
    default:
        mSpeedH = 0.0f;
        mSpeedV *= rate;
        break;
    }
    if (mIsRight != obj().target().isRightDir() && num != 0) {
        Utility::Turn(obj());
    }
}

StateJump::~StateJump() {}

void StateJump::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd() && mIsStart) {
        obj().model().reqScript(8);
        mIsStart = false;
    }
    if (mFrame == obj().param().pluid().mJumpAnimFrame) {
        obj().model().reqScript(1);
    }
}

void StateJump::procMove() {
    if (mFrame >= obj().param().pluid().mJumpStartFrame) {
        if (obj().footState().isGround()) {
            obj().footState().setAir();
            mIsJumped = true;
            obj().move().setSpeedH(mSpeedH);
            obj().move().setSpeedV(mSpeedV);
        }
        const common::ParamData& param = obj().param().common();
        const gobj::MoveParamAccel& accel = gobj::MoveParamAccel::Create(mSpeedH, 1.0f, 0.0f);
        obj().move().airAccelFall(obj().target().isRightDir(), accel, param.mFall);
    }
}

void StateJump::procFixPos() {
    if (obj().mapColl().result().isHitWallFront()) {
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    if (obj().mapColl().result().mIsHitFloor && mFrame > obj().param().pluid().mJumpStartFrame) {
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::pluid
