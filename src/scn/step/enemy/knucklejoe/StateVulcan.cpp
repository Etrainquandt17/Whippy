#include "scn/step/enemy/knucklejoe/StateVulcan.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/knucklejoe/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace knucklejoe {

StateVulcan::StateVulcan(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(0xd);
    obj().model().anim().setFrameRate(0.0f);
    obj().move().resetSpeedV();
    obj().move().resetSpeedH();
    obj().model().rotCtrl().setRotHTarget(90.0f);
    obj().model().rotCtrl().setRotHIntpRate(0.25f);
}

StateVulcan::~StateVulcan() {
    obj().model().rotCtrl().resetRotTarget();
    obj().model().rotCtrl().setRotHIntpRate(0.1f);
    obj().effect().state().releaseAndVanish();
}

void StateVulcan::procAnim() {
    if (mFrame++ == obj().param().knucklejoe().mVulcanFrame) {
        obj().model().anim().setFrameRate(1.0f);
    }
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateVulcan::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::knucklejoe
