#include "scn/step/weapon/spearspear/StateReflect.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/ocoll/HitResistLv.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/spearspear/Param.h"
#include "scn/step/weapon/spearspear/StateStickObj.h"
#include "scn/step/weapon/spearspear/StateStickWall.h"
#include "scn/step/weapon/spearspear/Utility.h"

using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace spearspear {

StateReflect::StateReflect(Weapon* weapon) : StateBase(weapon), mRot(0.0f) {
    const Param& param = obj().param().spearSpear();
    Vector3 velocity(param._28 * Math::Sign(obj().move().velocity().x), param._2C, 0.0f);
    obj().move().setVelocity(velocity);
}

StateReflect::~StateReflect() {
    obj().model().model().nodes().at(1).localMtx().reset();
}

void StateReflect::procAnim() {
    const Param& param = obj().param().spearSpear();
    Utility::Rotate(obj());
    mRot -= param._30;
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    if (mRot < 0.0f) {
        mRot += 360.0f;
    }
    obj().model().model().nodes().at(1).localMtx().setRTMtx(
        Matrix34::CreateRotXYZDeg(Vector3(0.0f, 0.0f, mRot))
    );
}

void StateReflect::procMove() {
    const Param& param = obj().param().spearSpear();
    obj().move().airDecelFall(param._10, param._14);
}

void StateReflect::procFixPos() {
    if (obj().mapColl().isHit()) {
        Vector3 velocity = obj().mapColl().normal().toVector3();
        velocity *= -0.1f;
        obj().move().setVelocity(velocity);
        f32 rot = obj().model().rotCtrl().getRotV();
        obj().stateChanger().setNextState<StateStickWall, Weapon*, f32>(&obj(), rot);
    } else if (obj().objColl().attack().isCollide()) {
        if (obj().objColl().attack().getCollidedHitResistLv() >= ocoll::HIT_RESIST_LV_REFLECT) {
            obj().stateChanger().setNextState<StateReflect, Weapon*>(&obj());
        } else if (obj().objColl().attack().getCollidedHitResistLv() == ocoll::HIT_RESIST_LV_WALL) {
            f32 rot = obj().model().rotCtrl().getRotV();
            obj().stateChanger().setNextState<StateStickObj, Weapon*, f32>(&obj(), rot);
        }
    }
}

void StateReflect::procObjCollReact() {}

}}}}  // namespace scn::step::weapon::spearspear
