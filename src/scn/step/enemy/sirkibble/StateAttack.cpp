#include "scn/step/enemy/sirkibble/StateAttack.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/sirkibble/Custom.h"
#include "scn/step/enemy/sirkibble/ParamData.h"
#include "scn/step/enemy/sirkibble/StateWait.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(7);
    custom.chkNextTurnJump();
    if (custom.isNextTurnJump()) {
        obj().target().invert();
    }
}

StateAttack::~StateAttack() {}

void StateAttack::procAnim() {
    const ParamData& param = obj().param().sirkibble();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mFrame++;
    if (mFrame == param.mAttackShotFrame) {
        custom.reqWeapon();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
    }
}

void StateAttack::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateAttack::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::sirkibble
