#include "scn/step/weapon/shotzobullet/StateMain.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
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

namespace scn {
namespace step {
namespace weapon {
namespace shotzobullet {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mRot(0.0f), mFrame(0) {
    f32 speed = obj().param().shotzoBullet()._0;
    mVelocity = obj().move().velocity() * speed;
    g3d::NodeAccessor node = obj().model().model().nodes().at(1);
    hel::math::Matrix34 mtx = node.localMtx().rtMtx();
    mtx.setT(hel::math::Vector3(0.0f, 0.0f, obj().param().shotzoBullet()._8));
    node.localMtx().setRTMtx(mtx);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x19B));
    obj().objColl().addAttack(1, 0.2f);
    obj().objColl().addHit(1, 0.2f);
}

void StateMain::procAnim() {
    mRot += obj().param().shotzoBullet()._4;
    g3d::NodeAccessor node = obj().model().model().nodes().at(0);
    node.localMtx().setRTMtx(hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3(1.0f, 0.0f, 0.0f), mRot));
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
