#include "scn/step/hero/fire/StateFireBurningWallHit.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/FireParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateHover.h"
#include "scn/step/hero/fire/StateFireBurning.h"
#include "util/StateChanger.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace fire {

StateFireBurningWallHit::StateFireBurningWallHit(Hero* hero)
    : StateBase(hero) {
    const FireParam& param = obj().param().fire();
    obj().footState().setAir();
    obj().model().setFixDir(true);
    obj().model().script().start(0xB4);
    // TODO: the two speeds trade f30 and f31; everything else matches.
    f32 speedH = param._90;
    f32 speedV = param._94;
    if (obj().model().isRightDir()) {
        speedH = -speedH;
    }
    Vector3 velocity(speedH, speedV, 0.0f);
    obj().move().setVelocity(velocity);
    obj().invincible().set(param._98);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
    obj().hitStop().set(10);
    Vector3 pos = static_cast<const Hero&>(obj()).location().pos();
    pos.y += param._9C;
    f32 sign = obj().model().isRightDir() ? 1.0f : -1.0f;
    pos.x += param._A0 * sign;
    obj().effect()._F8.requestP(static_cast<effect::Kind>(0x171), pos);
}

StateFireBurningWallHit::~StateFireBurningWallHit() {
}

void StateFireBurningWallHit::procAnim() {
    if (obj().move().velocity().y < 0.0f) {
        if (StateFireBurning::TryToChangeState(objPtr(), 0) || common::StateHover::TryToChangeState(objPtr())) {
            return;
        }
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
    }
}

void StateFireBurningWallHit::procMove() {
    const FireParam& param = obj().param().fire();
    gobj::MoveParamFall fall = obj().move().velocity().y > 0.0f ? param._A4 : obj().param().common()._90;
    obj().move().airDecelFall(param._B0, fall);
}

void StateFireBurningWallHit::procFixPos() {
}

}}}}  // namespace scn::step::hero::fire
