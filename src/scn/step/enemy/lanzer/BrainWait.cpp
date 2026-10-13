#include "scn/step/enemy/lanzer/BrainWait.h"

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
#include "scn/step/enemy/common/StateWait.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace lanzer {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<common::StateWait, Enemy*>(&obj());
    if (obj().variation() == 0x8a) {
        obj().target().setIsRightDir(false);
    } else if (obj().variation() == 0x8b) {
        obj().target().setIsRightDir(true);
    }
    return true;
}

bool BrainWait::onLanding() {
    return onStart();
}

void BrainWait::update() {
    if (obj().variation() == 0x89) {
        Utility::TurnHero(obj());
    }
}

}}}}  // namespace scn::step::enemy::lanzer
