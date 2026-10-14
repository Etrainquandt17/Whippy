#include "scn/step/weapon/shotzobullet/StateMain.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "ocoll/Hit.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/Water.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/shotzobullet/Param.h"

using g3d::NodeAccessor;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace shotzobullet {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mRot(0.0f), mFrame(0) {
    f32 speed = obj().param().shotzoBullet()._0;
    mVelocity = obj().move().velocity() * speed;
    NodeAccessor node = obj().model().model().nodes().at(1);
    Matrix34 mtx = node.localMtx().rtMtx();
    mtx.setT(Vector3(0.0f, 0.0f, obj().param().shotzoBullet()._8));
    node.localMtx().setRTMtx(mtx);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x19B));
    obj().objColl().addAttack(1, 0.2f);
    obj().objColl().addHit(1, 0.2f);
}

void StateMain::procAnim() {
    mRot += obj().param().shotzoBullet()._4;
    NodeAccessor node = obj().model().model().nodes().at(0);
    node.localMtx().setRTMtx(Matrix34::CreateRotAxisDeg(Vector3(1.0f, 0.0f, 0.0f), mRot));
    if (++mFrame > obj().param().shotzoBullet()._C) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x4DD), obj().location().pos());
        obj().dead();
    }
}

void StateMain::procMove() {
    obj().location().setPos(obj().location().pos() + mVelocity);
}

void StateMain::procObjCollReact() {
    if (obj().mapColl().isHit() || obj().objColl().hit().isCollide() || obj().water().isInWater()) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x4DD), obj().location().pos());
        obj().dead();
    }
}

}}}}  // namespace scn::step::weapon::shotzobullet
