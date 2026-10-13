#include "scn/step/enemy/whispyapple/StateAppear.h"

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
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/whispyapple/StateFall.h"
#include "scn/step/enemy/whispyapple/WhispyAppleUtility.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace whispyapple {

StateAppear::StateAppear(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().move().resetVelocity();
    obj().objColl().setBodyCollStateHitOnly();
    obj().model().reqScript(7);
}

StateAppear::~StateAppear() {
    obj().objColl().bodyColl().setStateNormal();
}

void StateAppear::procAnim() {
    if (obj().model().isAllEnd()) {
        WhispyAppleUtility::ReqFallSE(obj());
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

void StateAppear::procMove() {}

void StateAppear::procFixPos() {}

}}}}  // namespace scn::step::enemy::whispyapple
