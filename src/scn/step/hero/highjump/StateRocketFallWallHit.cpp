#include "scn/step/hero/highjump/StateRocketFallWallHit.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/HighjumpParam.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Landing.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/common/StateFall.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace highjump {

StateRocketFallWallHit::StateRocketFallWallHit(Hero* hero)
    : StateBase(hero)
    , _8(0) {
    const HighjumpParam& param = obj().param().highjump();
    obj().footState().setAir();
    obj().model().setFixDir(true);
    obj().invincible().set(param._B8);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
    obj().hitStop().set(param._BC);
    obj().move().setSpeedV(param._C0);
    obj().move().setSpeedH(param._C4 * obj().move().velocity().x);
    obj().landing().setValidAir(true);
    obj().model().script().start(0xFD);
}

StateRocketFallWallHit::~StateRocketFallWallHit() {
    obj().landing().setValidAir(false);
    const HighjumpParam& param = obj().param().highjump();
    obj().abilityManager().setActionInterval(param._C8);
}

void StateRocketFallWallHit::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
    }
}

void StateRocketFallWallHit::procMove() {
    const HighjumpParam& param = obj().param().highjump();
    obj().move().airDecelFall(param._CC, param._D0);
}

void StateRocketFallWallHit::procFixPos() {
}

}
}
}
}
