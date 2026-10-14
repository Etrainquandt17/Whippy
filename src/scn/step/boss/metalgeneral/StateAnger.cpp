#include "scn/step/boss/metalgeneral/StateAnger.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/StateWait.h"
#include "scn/step/chara/Model.h"
#include "scn/step/info/BossPanel.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateAnger::StateAnger(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(0xE);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_REFLECT);
    obj().invincible().setPermNoFlash();
    obj().guard().setType(static_cast<GuardType>(6));
    obj().infoBossPanel().transformStart();
    obj().effect().state().requestN(static_cast<effect::Kind>(0x461), 0);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x459), 5);
    obj().move().resetVelocity();
}

StateAnger::~StateAnger() {
    obj().infoBossPanel().transformEnd();
}

void StateAnger::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateAnger::procMove() {}

void StateAnger::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
