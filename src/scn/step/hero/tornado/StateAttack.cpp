#include "scn/step/hero/tornado/StateAttack.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/GroundChecker.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Landing.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/ShakeCharge.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/TornadoParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/tornado/StateChargeAttack.h"
#include "util/StateChanger.h"

using hel::math::Direction3;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace tornado {

bool StateAttack::TryToChangeState(Hero* hero) {
    if (hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateAttack, Hero*>(hero);
        return true;
    }
    return false;
}

StateAttack::StateAttack(Hero* hero)
    : StateBase(hero)
    , mTurnWait(0)
    , mDustWait(0)
    , mIsCharged(false)
    , mIsEnd(false) {
    obj().piggyback().unlinkAll();
    obj().model().script().start(0x126);
    Utility::AirAttackInitSpeedV(obj());
    setEnableCharge();
    obj().landing().setValidAir(true);
}

StateAttack::~StateAttack() {
    obj().landing().setValidAir(false);
    if (!mIsEnd) {
        obj().effect()._58.releaseAndVanish();
    }
    obj().effect()._80.release();
    obj().soundSE()._78.stop();
}

void StateAttack::procAnim() {
    const TornadoParam& param = obj().param().tornado();
    switch (obj().model().anim().currentG3DAnimIndex()) {
    case 0x152:
        obj().shakeCharge().reset();
        break;
    case 0x153:
        updateCharge();
        updateDustEffect();
        break;
    case 0x154:
    case 0x155:
        obj().shakeCharge().reset();
        break;
    }
    if (obj().model().scriptTrigger().get(0)) {
        if (tryToChangeChargeAttack()) {
            return;
        }
        obj().effect()._80.release();
        obj().soundSE()._78.stop();
    }
    if (obj().model().scriptTrigger().get(1)) {
        obj().footState().setAir();
    }
    if (obj().model().isAllEnd()) {
        obj().abilityManager().setActionInterval(param._7C);
        if (obj().mapColl().result().mIsHitFloor) {
            obj().footState().setGround();
        }
        mIsEnd = true;
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateAttack::procMove() {
    const TornadoParam& param = obj().param().tornado();
    if (mTurnWait != 0) {
        mTurnWait--;
    }
    switch (obj().model().anim().currentG3DAnimIndex()) {
    case 0x152:
        Utility::MoveFromKeyState(obj(), param._0, obj().param().common()._74, obj().param().common()._90);
        break;
    case 0x153:
        tornadoMove(param._C);
        break;
    case 0x154:
        tornadoMove(param._30);
        break;
    case 0x155:
        Utility::MoveFromKeyState(obj(), param._60, param._6C, param._70);
        break;
    }
}

void StateAttack::procFixPos() {
    const TornadoParam& param = obj().param().tornado();
    switch (obj().model().anim().currentG3DAnimIndex()) {
    case 0x152:
    case 0x154:
    case 0x155:
        Utility::MapCollReactDefaultAction(obj());
        break;
    }
}

bool StateAttack::procObjCollReact() {
    if (obj().model().anim().currentG3DAnimIndex() == 0x153) {
        if (obj().mapColl().result().isHitWall()) {
            turn();
        }
    }
    return false;
}

void StateAttack::tornadoMove(const ParamTornadoMove& move) {
    Utility::UpdateMoveTarget(obj());
    Vector3 velocity = obj().move().velocity();
    const TornadoParam& param = obj().param().tornado();
    if (obj().hid().isHold(4)) {
        velocity.y -= velocity.y > 0.0f ? move._8 * param._5C : move._8;
    } else if (obj().hid().isHold(0x28)) {
        velocity.y += velocity.y < 0.0f ? move._4 * param._58 : move._4;
        obj().footState().setAir();
    }
    if (mTurnWait == 0) {
        f32 sign = obj().target().getSign();
        velocity.x += velocity.x * sign > 0.0f ? sign * move._0 : param._54 * (sign * move._0);
    }
    velocity.x = Math::Limit(velocity.x, move._C);
    velocity.y = Math::Limit(velocity.y, move._10);
    obj().move().setVelocity(velocity);
    gobj::MoveParamAccel accel = gobj::MoveParamAccel::Create(move._C, 0.0f, move._14);
    if (obj().footState().isGround()) {
        obj().move().groundAccel(obj().target().isRightDir(), accel);
    } else {
        obj().move().airAccelFall(obj().target().isRightDir(), accel, move._18);
    }
}

void StateAttack::turn() {
    if (mTurnWait != 0) {
        return;
    }
    const TornadoParam& param = obj().param().tornado();
    mTurnWait = param._84;
    Vector3 velocity = obj().move().velocity();
    velocity.x *= -param._80;
    obj().move().setVelocity(velocity);
    obj().target().invert();
    obj().soundSE()._4.start(0x1E4);
}

void StateAttack::updateDustEffect() {
    if (mDustWait != 0) {
        mDustWait--;
        return;
    }
    if (!obj().groundChecker().isFloorValid()) {
        return;
    }
    Vector3 floorPos = obj().groundChecker().getFloorPos().toVector3();
    const TornadoParam& param = obj().param().tornado();
    f32 height = static_cast<const Hero&>(obj()).location().pos().y - floorPos.y;
    if (Math::AbsF32(height) < param._88) {
        mDustWait = param._8C;
        obj().effect()._58.requestPD(static_cast<effect::Kind>(0x540), floorPos, Direction3::BASIS);
    }
}

void StateAttack::setEnableCharge() {
    const TornadoParam& param = obj().param().tornado();
    obj().shakeCharge().setEnv(param._90, param._94, param._98, param._9C);
    obj().shakeCharge().reset();
}

void StateAttack::updateCharge() {
    if (mIsCharged) {
        return;
    }
    const TornadoParam& param = obj().param().tornado();
    if (param._98 == obj().shakeCharge().power()) {
        mIsCharged = true;
        hero::Effect& effect = obj().effect();
        effect._58.requestND(static_cast<effect::Kind>(0x547), 0, obj().model().getDirection3());
        obj().soundSE()._78.stop();
        obj().soundSE()._4.start(0x14D);
        return;
    }
    if (obj().shakeCharge().power() >= param._A0) {
        if (obj().shakeCharge().powerPrev() < param._A0) {
            obj().effect()._80.requestN(static_cast<effect::Kind>(0x546), 2);
        }
    } else if (obj().shakeCharge().powerPrev() >= param._A0) {
        obj().effect()._80.release();
    }
    if (obj().shakeCharge().power() >= param._A4) {
        if (obj().shakeCharge().powerPrev() < param._A4) {
            obj().soundSE()._78.start(0x149);
        }
    } else if (obj().shakeCharge().powerPrev() >= param._A4) {
        obj().soundSE()._78.stop();
    }
}

bool StateAttack::tryToChangeChargeAttack() {
    if (mIsCharged) {
        mIsEnd = true;
        obj().stateChanger().setNextState<StateChargeAttack, Hero*>(objPtr());
        return true;
    }
    return false;
}

}}}}  // namespace scn::step::hero::tornado
