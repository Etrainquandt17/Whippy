#include "scn/step/enemy/cappy/BrainAttack.h"

#include "gobj/FootState.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/cappy/Custom.h"
#include "scn/step/enemy/cappy/StateAttack.h"
#include "scn/step/enemy/cappy/StateLostHat.h"
#include "scn/step/enemy/common/StateWait.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace cappy {

BrainAttack::BrainAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainAttack::onStart() {
    obj().stateChanger().setNextState<StateAttack, Enemy*>(&obj());
    return true;
}

bool BrainAttack::onLanding() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isLostHat()) {
        obj().stateChanger().setNextState<StateLostHat, Enemy*>(&obj());
    } else {
        custom.enableCatch();
        if (custom.cap()) {
            custom.setThrowCount(120);
        } else {
            custom.setThrowCount(0);
        }
        obj().stateChanger().setNextState<common::StateWait, Enemy*>(&obj());
    }
    return true;
}

void BrainAttack::update() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().footState().isGround() && custom.isValidTurn()) {
        Utility::TurnHero(obj());
    }
}

}}}}  // namespace scn::step::enemy::cappy
