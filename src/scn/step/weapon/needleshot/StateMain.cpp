#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/weapon/needleshot/StateMain.h"

#include "g3d/NodeAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "ocoll/AttackResult.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/ocoll/HitResistLv.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/needleshot/Param.h"
#include "scn/step/weapon/needleshot/StateReflect.h"
#include "scn/step/weapon/needleshot/StateStickEnemy.h"
#include "scn/step/weapon/needleshot/StateStickObj.h"
#include "scn/step/weapon/needleshot/StateStickWall.h"

using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace weapon {
namespace needleshot {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mIsDead(false), mRot(0.0f) {
    const Param& param = obj().param().needleShot();
    Vector3 velocity = obj().move().velocity();
    mRot = Math::Atan2DegF(velocity.y, velocity.x);
    if (!obj().target().isRightDir()) {
        mRot += 180.0f;
    }
    obj().model().rotCtrl().initRotV(mRot);
    f32 length = param._1C * obj().target().getSign();
    obj().mapColl().setActorOffset(
        Vector2(length * Math::CosDegF(mRot), length * Math::SinDegF(mRot))
    );
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x53));
    obj().objColl().addAttack(0, obj().param().needleShot()._0);
}

StateMain::~StateMain() {
    obj().model().model().nodes().at(1).setVisibilityBelow(false);
}

void StateMain::procAnim() {
    if (mIsDead) {
        obj().dead();
    }
}

void StateMain::procMove() {
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Zero();
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(decel, fall);
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {
    if (obj().objColl().attack().isCollide()) {
        u32 lv = obj().objColl().attack().getCollidedHitResistLv();
        if (lv >= ocoll::HIT_RESIST_LV_REPEL) {
            obj().stateChanger().setNextState<StateReflect, Weapon*>(&obj());
        } else if (lv == ocoll::HIT_RESIST_LV_WALL) {
            obj().stateChanger().setNextState<StateStickObj, Weapon*>(&obj());
        } else {
            u64 uid = obj().objColl().attack().result().getData(0).mOwnerID;
            obj().stateChanger().setNextState<StateStickEnemy, Weapon*, ObjRefHandle<enemy::Enemy> >(
                &obj(), obj().comp().enemyManager().getEnemyByOCollOwnerUID(uid)
            );
        }
    } else if (obj().objColl().attack().isCollideGimmick()) {
        dead();
    } else if (isHitMap()) {
        updateMapColl();
        obj().stateChanger().setNextState<StateStickWall, Weapon*>(&obj());
    }
}

void StateMain::dead() {
    if (!mIsDead) {
        mIsDead = true;
    }
}

bool StateMain::isHitMap() {
    MapColl& mapColl = obj().mapColl();
    if (!mapColl.isHit()) {
        return false;
    }
    Vector2 velocity = obj().move().velocity().getXY();
    if (Math::EqZero(velocity.y) && mapColl.result().isHitWallFront()) {
        return true;
    }
    const Vector2& normal = mapColl.normal();
    if (Math::Equals(velocity.cos(normal), 0.0f, 0.00001f)) {
        return false;
    }
    return velocity.cos(normal) < 0.0f;
}

void StateMain::updateMapColl() {
    f32 length = obj().param().needleShot()._1C;
    f32 sign = obj().target().getSign();
    f32 signedLength = sign * length;
    Vector3 offset(
        signedLength * Math::CosDegF(mRot), signedLength * Math::SinDegF(mRot), 0.0f
    );
    Vector3 pos = obj().mapColl().intersectPos().toVector3() - offset;
    if (obj().mapColl().result().isHitFloor()) {
        pos.y += 0.1f;
    } else if (obj().mapColl().result().isHitRoof()) {
        pos.y -= 0.1f;
    } else if (obj().mapColl().result().isHitWall()) {
        pos.x += obj().mapColl().normal().x > 0.0f ? 0.1f : -0.1f;
    }
    obj().location().setPos(pos);
    obj().mapColl().reset();
    Vector3 velocity = obj().mapColl().normal().toVector3();
    velocity *= -0.1f;
    obj().move().setVelocity(velocity);
    obj().move().decel(gobj::MoveParamDecel::Zero());
    obj().mapColl().procMapColl();
}

}}}}  // namespace scn::step::weapon::needleshot
