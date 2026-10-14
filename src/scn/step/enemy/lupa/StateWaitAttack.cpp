#include "scn/step/enemy/lupa/StateWaitAttack.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/lupa/Custom.h"
#include "scn/step/enemy/lupa/ParamData.h"
#include "scn/step/enemy/lupa/StateWait.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace lupa {

StateWaitAttack::StateWaitAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().model().reqScript(7);
}

StateWaitAttack::~StateWaitAttack() {}

void StateWaitAttack::procAnim() {
    const ParamData& param = obj().param().lupa();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mFrame++;
    Utility::TurnHero(obj());
    if (mFrame == param.mWaitAttackShotFrame) {
        custom.reqShot();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
    }
}

void StateWaitAttack::procMove() {
    const ParamData& param = obj().param().lupa();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().move().decel(param.mWaitDecel);
    custom.approachMap();
}

void StateWaitAttack::procFixPos() {}

}}}}  // namespace scn::step::enemy::lupa
