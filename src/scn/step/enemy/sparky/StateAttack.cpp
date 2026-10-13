#include "scn/step/enemy/sparky/StateAttack.h"

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
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/common/StateWait.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace sparky {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy) {
    obj().model().reqScript(12);
}

StateAttack::~StateAttack() {
    obj().effect().state().releaseAndVanish();
}

void StateAttack::procAnim() {
    if (obj().model().anim().currentG3DAnimIndex() == 7) {
        Utility::SetTargetByDirType(obj());
    }
    if (obj().model().isAllEnd()) {
        obj().move().resetVelocity();
        obj().stateChanger().setNextState<common::StateWait, Enemy*>(objPtr());
    }
}

void StateAttack::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::sparky
