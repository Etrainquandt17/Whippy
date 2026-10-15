#include "scn/step/boss/goliath/StateWallThrow.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateWallWait.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateWallThrow::StateWallThrow(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::ControlHateOnAction(obj());
    obj().model().reqScript(0xD);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateWallThrow::~StateWallThrow() {}

void StateWallThrow::procAnim() {}

void StateWallThrow::procMove() {
    if (obj().scriptTrigger().get(0)) {
        generateEnemy();
    }
    if (obj().scriptTrigger().get(1)) {
        throwEnemy();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWallWait, Boss*>(objPtr());
    }
}

void StateWallThrow::procFixPos() {}

void StateWallThrow::generateEnemy() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).enemyCtrl().request();
}

void StateWallThrow::throwEnemy() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).enemyCtrl().throwEnemy();
}

}}}}  // namespace scn::step::boss::goliath
