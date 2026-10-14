#include "scn/step/enemy/carrydee/StateJump.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/carrydee/Custom.h"
#include "scn/step/enemy/carrydee/ParamData.h"
#include "scn/step/enemy/carrydee/StateCarry.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace carrydee {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(0xb);
}

StateJump::~StateJump() {}

void StateJump::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(8);
    }
}

void StateJump::procMove() {
    const ParamData& param = obj().param().carrydee();
    if (mFrame >= param.mJumpFrame) {
        if (obj().footState().isGround()) {
            obj().footState().setAir();
            obj().move().setSpeedV(param.mJumpSpeedV);
            obj().move().setSpeedH(param.mJumpSpeedH);
        }
        obj().move().airAccelFall(obj().target().isRightDir(), param.mJumpAccel, param.mJumpFall);
    }
    DynamicCastToRef<Custom, ICustom>(obj().custom()).fixPosKey();
}

void StateJump::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor && mFrame > obj().param().carrydee().mJumpFrame) {
        obj().stateChanger().setNextState<StateCarry, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::carrydee
