#include "scn/step/enemy/parasoldoo/BrainWalk.h"

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
#include "scn/step/enemy/parasoldoo/StateFall.h"
#include "scn/step/enemy/parasoldoo/StateParasolFall.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasoldoo {

BrainWalk::BrainWalk(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalk::onStart() {
    obj().stateChanger().setNextState<StateParasolFall, Enemy*>(&obj());
    return true;
}

bool BrainWalk::onRecover() {
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

void BrainWalk::update() {
    Utility::ChkNururiTurn(obj());
}

}}}}  // namespace scn::step::enemy::parasoldoo
