#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/boss/goliath/StateSwoopRotateLanding.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/boss/goliath/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateSwoopRotateLanding::StateSwoopRotateLanding(Boss* boss) : StateBase(boss), mRotState(0), mRot(0.0f), mRotSpeed(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::ControlHateOnAction(obj());
    obj().model().reqScript(0x12);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateSwoopRotateLanding::~StateSwoopRotateLanding() {}

void StateSwoopRotateLanding::procAnim() {
    const Param& param = obj().param().goliath();
    if (obj().scriptTrigger().get(0)) {
        generateIceBall(param._A8, param._B0);
        generateIceBall(-param._A8, -param._B0);
    }
    if (obj().scriptTrigger().get(1)) {
        generateIceBall(param._A8, param._AC);
        generateIceBall(-param._A8, -param._AC);
    }
    if (obj().scriptTrigger().get(2)) {
        mRotState = 1;
        obj().model().rotCtrl().setRotHTarget(0.0f);
        obj().model().rotCtrl().setRotHIntpRate(param._A4);
    }
    if (obj().scriptTrigger().get(3)) {
        mRotState = 2;
        obj().model().rotCtrl().setRotHIntpRate(0.1f);
        obj().model().rotCtrl().resetRotTarget();
    }
    updateRotate();
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateSwoopRotateLanding::procMove() {}

void StateSwoopRotateLanding::procFixPos() {}

void StateSwoopRotateLanding::updateRotate() {
    const Param& param = obj().param().goliath();
    switch (mRotState) {
    case 0:
        mRotSpeed = Math::LimitMax(mRotSpeed + param._A0, param._9C);
        mRot += mRotSpeed;
        if (mRot > 0.0f) {
            mRot -= 360.0f;
        }
        obj().model().rotCtrl().initRotH(mRot);
        break;
    case 2:
        Utility::TurnHatedHero(obj());
        break;
    }
}

void StateSwoopRotateLanding::generateIceBall(f32 offsetX, f32 speedX) {
    const Param& param = obj().param().goliath();
    Vector3 pos = obj().location().pos();
    pos.x += offsetX;
    enemy::Desc desc(static_cast<map::BinEnemyKind>(0x83), static_cast<map::BinEnemyVariation>(0x177), 0,
                     static_cast<map::BinEnemyDirType>(0), static_cast<map::BinEnemySize>(0), false, false, pos.getXY());
    Vector2 speed(speedX, param._B4);
    ObjRefHandle<enemy::Enemy> enemy = obj().comp().enemyManager().request(desc);
    if (enemy.isAlive()) {
        enemy->move().setVelocity(speed.toVector3());
    }
}

}}}}  // namespace scn::step::boss::goliath
