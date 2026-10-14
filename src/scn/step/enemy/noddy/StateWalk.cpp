#include "scn/step/enemy/noddy/StateWalk.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/noddy/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace noddy {

StateWalk::StateWalk(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(3);
    obj().brainCtrl().toValid();
}

StateWalk::~StateWalk() {}

void StateWalk::procMove() {
    const ParamData& param = obj().param().noddy();
    obj().move().groundAccel(obj().target().isRightDir(), param.mAccel);
}

void StateWalk::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result._2) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::noddy
