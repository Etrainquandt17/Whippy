#include "scn/step/enemy/owgulf/StateFlyWaitFix.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

StateFlyWaitFix::StateFlyWaitFix(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(4);
    obj().brainCtrl().toValid();
}

void StateFlyWaitFix::procMove() {
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Create(0.02f);
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Create(0.0f, 0.0f, 0.02f);
    obj().move().airDecelFall(decel, fall);
}

}}}}  // namespace scn::step::enemy::owgulf
