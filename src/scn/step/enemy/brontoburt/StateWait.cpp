#include "scn/step/enemy/brontoburt/StateWait.h"

#include "gobj/FootState.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/brontoburt/StateTakeOff.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(0);
    Utility::SetTargetByDirType(obj());
}

void StateWait::procFixPos() {
    if (!Utility::IsFixDirType(obj())) {
        Utility::TurnHero(obj());
    }
    if (Utility::IsHeroInRange(obj(), 8.0f, -8.0f, -7.5f, 7.5f) || !obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateTakeOff, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::brontoburt
