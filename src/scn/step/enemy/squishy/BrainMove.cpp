#include "scn/step/enemy/squishy/BrainMove.h"

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
#include "scn/step/enemy/squishy/Custom.h"
#include "scn/step/enemy/squishy/StateFall.h"
#include "scn/step/enemy/squishy/StateMoveOnLand.h"
#include "scn/step/enemy/squishy/StateWait.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    if (hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).isInWater(false)) {
        obj().brainCtrl().toValid();
    } else if (obj().variation() == 0x9f) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateMoveOnLand, Enemy*>(&obj());
    }
    return true;
}

bool BrainMove::onRecover() {
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::squishy
