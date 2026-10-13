#include "scn/step/enemy/bouncy/StateGrandLowperEscapeStart.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
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
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/bouncy/StateGrandLowperEscape.h"
#include "scn/step/enemy/common/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace bouncy {

StateGrandLowperEscapeStart::StateGrandLowperEscapeStart(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().move().resetVelocity();
    obj().model().reqScript(8);
}

StateGrandLowperEscapeStart::~StateGrandLowperEscapeStart() {}

void StateGrandLowperEscapeStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateGrandLowperEscape, Enemy*>(objPtr());
    }
}

void StateGrandLowperEscapeStart::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateGrandLowperEscapeStart::procFixPos() {}

}}}}  // namespace scn::step::enemy::bouncy
