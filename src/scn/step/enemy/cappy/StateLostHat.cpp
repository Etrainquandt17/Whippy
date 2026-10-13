#include "scn/step/enemy/cappy/StateLostHat.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/cappy/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace cappy {

StateLostHat::StateLostHat(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(8);
}

StateLostHat::~StateLostHat() {}

void StateLostHat::procAnim() {
    if (obj().model().anim().currentG3DAnimIndex() == 8) {
        mFrame++;
        if (mFrame > 10) {
            Utility::TurnHero(obj());
        }
    }
    if (obj().model().isAllEnd()) {
        if (obj().model().anim().currentG3DAnimIndex() != 7) {
            obj().model().reqScript(8);
        } else {
            obj().model().reqScript(9);
            mFrame = 0;
        }
    }
}

void StateLostHat::procMove() {
    const ParamData& param = obj().param().cappy();
    obj().move().groundDecel(param.mDecel);
}

void StateLostHat::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::cappy
