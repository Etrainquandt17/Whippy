#include "scn/step/enemy/sirkibble/StateJumpAttack.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/sirkibble/Custom.h"
#include "scn/step/enemy/sirkibble/ParamData.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {

StateJumpAttack::StateJumpAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(11);
    obj().move().resetVelocity();
}

StateJumpAttack::~StateJumpAttack() {}

void StateJumpAttack::procAnim() {
    const ParamData& param = obj().param().sirkibble();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mFrame++;
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    } else if (mFrame == param.mJumpAttackShotFrame) {
        custom.reqWeapon();
    }
}

void StateJumpAttack::procMove() {
    const ParamData& param = obj().param().sirkibble();
    if (mFrame > param.mJumpAttackShotFrame + 5) {
        obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), param.mJumpFall);
    }
}

void StateJumpAttack::procFixPos() {}

}}}}  // namespace scn::step::enemy::sirkibble
