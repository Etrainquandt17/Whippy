#include "scn/step/hero/wing/StateShuttleLoop.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearAnim.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/hero/CameraTarget.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Gear.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/WingParam.h"
#include "scn/step/hero/wing/StateShuttleLoopEnd.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace wing {

bool StateShuttleLoop::TryToChangeState(Hero* hero) {
    if (hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateShuttleLoop, Hero*>(hero);
        return true;
    }
    return false;
}

StateShuttleLoop::StateShuttleLoop(Hero* hero)
    : StateBase(hero)
    , mPrevPos() {
    obj().piggyback().unlinkAll();
    obj().invincible().setPerm();
    if (obj().footState().isGround()) {
        obj().footState().setAir();
    }
    obj().model().script().start(0x155);
    obj().cameraTarget().setZeroIntpRate();
}

StateShuttleLoop::~StateShuttleLoop() {
    obj().soundSE()._78.stop();
    if (obj().model().hat().isValid()) {
        obj().model().hat().anim().start(0x18, false);
    }
}

void StateShuttleLoop::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().effect()._58.releaseAndVanish();
        obj().stateChanger().setNextState<StateShuttleLoopEnd, Hero*>(objPtr());
    }
}

void StateShuttleLoop::procMove() {
    const WingParam& param = obj().param().wing();
    f32 t = obj().model().anim().frame() / obj().model().anim().totalFrame();
    f32 rate = 1.5f * t + -0.5f * t * t;
    hel::math::Vector2 pos;
    pos.x = param._C8 * hel::math::Math::SinDegF(rate * param._C4);
    pos.x *= obj().model().getSign();
    pos.y = param._CC * (1.0f - hel::math::Math::CosDegF(rate * param._C4));
    hel::math::Vector2 velocity = pos - mPrevPos;
    mPrevPos = pos;
    obj().move().setVelocity(velocity.toVector3());
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateShuttleLoop::procFixPos() {
}

}}}}  // namespace scn::step::hero::wing
