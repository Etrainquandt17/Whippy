#include "scn/step/enemy/leafan/StateLanding.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/leafan/StateFall.h"
#include "scn/step/enemy/leafan/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace leafan {

StateLanding::StateLanding(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(2);
}

StateLanding::~StateLanding() {}

void StateLanding::procAnim() {
    if (Utility::IsCameraOut(obj())) {
        if (!obj().brainCtrl().onLanding()) {
            obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
        }
    } else if (obj().model().isAllEnd()) {
        if (!obj().brainCtrl().onLanding()) {
            obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
        }
    }
}

void StateLanding::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateLanding::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::leafan
