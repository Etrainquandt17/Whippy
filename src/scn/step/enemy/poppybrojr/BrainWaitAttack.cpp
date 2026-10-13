#include "scn/step/enemy/poppybrojr/BrainWaitAttack.h"

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
namespace poppybrojr {

BrainWaitAttack::BrainWaitAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWaitAttack::onStart() {
    obj().stateChanger().setNextState<common::StateWait, Enemy*>(&obj());
    return true;
}

bool BrainWaitAttack::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::poppybrojr
