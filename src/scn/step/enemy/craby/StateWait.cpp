#include "scn/step/enemy/craby/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/craby/Custom.h"
#include "scn/step/enemy/craby/StateAttack.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace craby {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().move().resetSpeedH();
    obj().model().reqScript(0);
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isPlayerInAimArea()) {
        obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
    }
}

void StateWait::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).reset();
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::craby
