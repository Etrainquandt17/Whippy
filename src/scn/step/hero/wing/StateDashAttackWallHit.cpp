#include "scn/step/hero/wing/StateDashAttackWallHit.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/WingParam.h"
#include "scn/step/hero/common/StateFall.h"
#include "util/StateChanger.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace hero {
namespace wing {

StateDashAttackWallHit::StateDashAttackWallHit(Hero* hero)
    : StateBase(hero) {
    obj().footState().setAir();
    obj().model().setFixDir(true);
    obj().model().script().start(0x153);
    const hel::math::Vec2& paramSpeed = obj().param().wing()._B0;
    Vector2 speed(paramSpeed.x, paramSpeed.y);
    speed.x *= obj().model().getSign();
    obj().move().setVelocity(speed.toVector3());
    obj().invincible().set(0x14);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
    obj().hitStop().set(0xA);
}

StateDashAttackWallHit::~StateDashAttackWallHit() {
    if (obj().model().hat().isValid()) {
        obj().model().hat().anim().start(0x18, false);
    }
}

void StateDashAttackWallHit::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
    }
}

void StateDashAttackWallHit::procMove() {
    gobj::MoveParamFall fall = obj().move().velocity().y > 0.0f ? gobj::MoveParamFall::Create(0.2f, 0.02f, 0.005f)
                                                                : obj().param().common()._90;
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.001f), fall);
}

void StateDashAttackWallHit::procFixPos() {
}

}}}}  // namespace scn::step::hero::wing
