#include "scn/step/enemy/flamer/BrainMove.h"

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
#include "scn/step/enemy/flamer/Custom.h"
#include "scn/step/enemy/flamer/StateMove.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace flamer {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setIsMove(true);
}

bool BrainMove::onStart() {
    if (obj().variation() == 0x29) {
        obj().stateChanger().setNextState<StateMoveCCW, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateMoveCWR, Enemy*>(&obj());
    }
    return true;
}

bool BrainMove::onRecover() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setIsMove(false);
    return false;
}

}}}}  // namespace scn::step::enemy::flamer
