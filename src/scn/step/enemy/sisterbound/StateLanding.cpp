#include "scn/step/enemy/sisterbound/StateLanding.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/sisterbound/ParamData.h"
#include "scn/step/enemy/sisterbound/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace sisterbound {

StateLanding::StateLanding(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(2);
    obj().model().anim().setFrameRate(obj().param().sisterbound().mLandingFrameRate);
}

StateLanding::~StateLanding() {}

void StateLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateLanding::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::sisterbound
