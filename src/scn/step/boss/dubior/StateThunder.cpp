#include "scn/step/boss/dubior/StateThunder.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/dubior/Custom.h"
#include "scn/step/boss/dubior/Param.h"
#include "scn/step/boss/dubior/StateWait.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

StateThunder::StateThunder(Boss* boss) : StateBase(boss) {
    obj().footState().setAir();
    obj().model().reqScript(10);
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1B0));
}

StateThunder::~StateThunder() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AB));
}

void StateThunder::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        custom.reqThunderGroundEffect();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateThunder::procMove() {
    const Param& param = obj().param().dubior();
    obj().move().decel(param._4C);
}

void StateThunder::procFixPos() {}

}}}}  // namespace scn::step::boss::dubior
