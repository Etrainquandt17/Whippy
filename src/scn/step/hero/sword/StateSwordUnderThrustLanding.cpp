#include "scn/step/hero/sword/StateSwordUnderThrustLanding.h"
#include "gobj/Move.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/Component.h"
#include "gobj/FootState.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/SwordParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateWait.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

StateSwordUnderThrustLanding::StateSwordUnderThrustLanding(Hero* hero)
    : StateBase(hero) {
    obj().footState().setGround();
    obj().model().script().start(0x7D);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
    const SwordParam& param = obj().param().sword();
    obj().invincible().set(param._A8);
}

StateSwordUnderThrustLanding::~StateSwordUnderThrustLanding() {
}

void StateSwordUnderThrustLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateWait, Hero*>(objPtr());
    }
}

void StateSwordUnderThrustLanding::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateSwordUnderThrustLanding::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(&obj());
    }
}

}}}}  // namespace scn::step::hero::sword
