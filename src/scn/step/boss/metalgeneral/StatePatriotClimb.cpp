#include "scn/step/boss/metalgeneral/StatePatriotClimb.h"

#include "g3d/NodeAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/StateFall.h"
#include "scn/step/boss/metalgeneral/StatePatriotLaunch.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StatePatriotClimb::StatePatriotClimb(Boss* boss) : StateBase(boss), mIsSignaled(false) {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0x24);
    mStartPos = obj().location().pos();
    if (custom.weaponCtrl().isHoldPatriot()) {
        mGoalPos = custom.weaponCtrl().patriotPos();
    }
    custom.collisionCtrl().setState(CollisionCtrl::STATE_PATRIOT);
    obj().guard().setType(static_cast<GuardType>(5));
    obj().mapColl().setValid(false);
    if (!Math::EqZero(obj().location().pos().z)) {
        obj().model().rotCtrl().setRotHTarget(param._1E0);
    } else {
        obj().model().rotCtrl().setRotHTarget(90.0f);
    }
}

StatePatriotClimb::~StatePatriotClimb() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().hitPoint().isDead() || !custom.weaponCtrl().isHoldPatriot()) {
        obj().mapColl().setValid(false);
        f32 diff;
        {
            NodeAccessor body = obj().model().model().nodes().at(5);
            NodeAccessor root = obj().model().model().nodes().at(0);
            diff = body.worldTrans().x - root.worldTrans().x;
        }
        Vector3 pos = obj().location().pos();
        pos.x += diff;
        obj().location().setPos(pos);
        obj().mapColl().setValid(true);
    }
}

void StatePatriotClimb::procAnim() {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().model().isAllEnd()) {
        if (!mIsSignaled) {
            mIsSignaled = true;
            custom.weaponCtrl().signalPatriot(enemy::metalgeneralpatriot::SIGNAL_KIND_1);
        } else if (custom.weaponCtrl().isPermitLaunch()) {
            obj().stateChanger().setNextState<StatePatriotLaunch, Boss*>(objPtr());
            return;
        }
    }
    if (!custom.weaponCtrl().isHoldPatriot()) {
        Vector3 velocity = param._2B4;
        velocity.x *= obj().target().getSign();
        obj().move().setVelocity(velocity);
        obj().stateChanger().setNextState<StateFall, Boss*>(objPtr());
    }
}

void StatePatriotClimb::procMove() {
    f32 total = static_cast<f32>(obj().model().anim().totalFrame());
    f32 t = obj().model().anim().frame() / total;
    f32 rate = Math::SinDegF(90.0f * t);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, rate);
    obj().location().setPos(pos);
}

void StatePatriotClimb::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
