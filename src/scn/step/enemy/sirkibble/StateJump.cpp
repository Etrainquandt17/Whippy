#include "scn/step/enemy/sirkibble/StateJump.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/sirkibble/Custom.h"
#include "scn/step/enemy/sirkibble/ParamData.h"
#include "scn/step/enemy/sirkibble/StateJumpAttack.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(10);
}

StateJump::~StateJump() {}

void StateJump::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mFrame++;
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(1);
    }
    if (obj().move().velocity().y < 0.0f) {
        if (custom.isPlayerUpPos()) {
            obj().stateChanger().setNextState<StateJumpAttack, Enemy*>(objPtr());
        } else {
            obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
        }
    }
}

void StateJump::procMove() {
    const ParamData& param = obj().param().sirkibble();
    if (mFrame >= param.mJumpStartFrame) {
        if (obj().footState().isGround()) {
            obj().footState().setAir();
            obj().move().setSpeedV(param.mJumpSpeed);
            obj().move().setSpeedH(0.0f);
        }
        obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), param.mJumpFall);
    }
}

void StateJump::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        if (obj().footState().isGround()) {
            obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
        }
    } else if (mFrame > obj().param().sirkibble().mJumpStartFrame) {
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::sirkibble
