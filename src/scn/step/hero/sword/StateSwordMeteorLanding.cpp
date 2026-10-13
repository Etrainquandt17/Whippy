#include "scn/step/hero/sword/StateSwordMeteorLanding.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/Component.h"
#include "gobj/FootState.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/SwordParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateSlidingHit.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

StateSwordMeteorLanding::StateSwordMeteorLanding(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().footState().setGround();
    obj().model().script().start(0x82);
    obj().move().resetVelocity();
    const SwordParam& param = obj().param().sword();
    obj().invincible().set(param._40);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
}

StateSwordMeteorLanding::~StateSwordMeteorLanding() {
}

void StateSwordMeteorLanding::procAnim() {
    if (++mFrame == obj().param().sword()._40) {
        obj().stateChanger().setNextState<common::StateSlidingHit, Hero*>(objPtr());
    }
}

void StateSwordMeteorLanding::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateSwordMeteorLanding::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
