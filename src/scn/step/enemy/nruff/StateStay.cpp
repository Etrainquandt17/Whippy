#include "scn/step/enemy/nruff/StateStay.h"

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
#include "scn/step/enemy/nruff/StateFall.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace nruff {

StateStay::StateStay(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(0);
    obj().move().resetSpeedV();
    obj().move().resetSpeedH();
}

StateStay::~StateStay() {}

void StateStay::procAnim() {
    mFrame++;
    if (mFrame == 0x23 || mFrame == 0x37 || mFrame == 0x50) {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x124), 0);
    }
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(3);
        obj().brainCtrl().toValid();
    }
}

void StateStay::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().model().reqScript(3);
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::nruff
