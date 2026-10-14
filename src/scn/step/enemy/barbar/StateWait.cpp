#include "scn/step/enemy/barbar/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace barbar {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(4);
    obj().brainCtrl().toValid();
    obj().move().resetSpeedV();
}

StateWait::~StateWait() {}

void StateWait::procAnim() {}

void StateWait::procMove() {
    obj().move().decel(obj().param().common().mDecel);
}

void StateWait::procFixPos() {}

}}}}  // namespace scn::step::enemy::barbar
