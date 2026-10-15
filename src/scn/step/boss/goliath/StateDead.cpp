#include "scn/step/boss/goliath/StateDead.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateDeadFall.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateDead::StateDead(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().target().setIsRightDir(false);
    obj().model().reqScript(4);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
}

StateDead::~StateDead() {}

void StateDead::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateDeadFall, Boss*>(objPtr());
    }
}

void StateDead::procMove() {}

void StateDead::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
