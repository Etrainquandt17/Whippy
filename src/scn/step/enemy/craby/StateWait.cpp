#include "scn/step/enemy/craby/StateWait.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
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
#include "scn/step/enemy/craby/Custom.h"
#include "scn/step/enemy/craby/StateAttack.h"
#include "snd/SERequestor.h"

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
