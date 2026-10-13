#include "scn/step/enemy/hothead/BrainAttack.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateWalkStraight.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace hothead {

BrainAttack::BrainAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainAttack::onStart() {
    if (obj().variation() == 0x11b || obj().variation() == 0x11c) {
        obj().stateChanger().setNextState<common::StateWalkStraight, Enemy*>(&obj());
        return true;
    }
    return false;
}

bool BrainAttack::onRecover() {
    return onStart();
}

bool BrainAttack::onLanding() {
    return onStart();
}

void BrainAttack::update() {
    if (obj().variation() == 0x11b || obj().variation() == 0x11c) {
        Utility::ChkNururiTurn(obj());
        Utility::ChkCliffTurn(obj());
    }
}

}}}}  // namespace scn::step::enemy::hothead
