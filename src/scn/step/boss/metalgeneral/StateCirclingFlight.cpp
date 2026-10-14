#include "scn/step/boss/metalgeneral/StateCirclingFlight.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/StateCirclingFlightEnd.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateCirclingFlight::StateCirclingFlight(Boss* boss) : StateBase(boss), mDir(), mRot(0.0f) {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0x1C);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_CIRCLING_FLIGHT);
    mDir = Utility::GetHatedHeroPos(obj()) - obj().location().pos();
    Utility::ControlHateOnAction(obj());
    if (mDir.y > 0.0f) {
        if (mDir.y / Math::Abs(mDir.x) > param._184) {
            mDir.x = Math::SignF32(mDir.x);
            mDir.y = param._184;
        }
    } else {
        if (mDir.y / Math::Abs(mDir.x) < param._188) {
            mDir.x = Math::SignF32(mDir.x);
            mDir.y = param._188;
        }
    }
    if (mDir.x * obj().target().getSign() < 0.0f) {
        mDir.x *= -1.0f;
    }
    mDir.normalize();
    Vector3 velocity = mDir * param._180;
    obj().move().setVelocity(velocity);
    if (Utility::IsVariationExtra(obj())) {
        obj().model().rotCtrl().setRotHTarget(90.0f);
    }
}

StateCirclingFlight::~StateCirclingFlight() {
    if (Utility::IsVariationExtra(obj())) {
        obj().model().rotCtrl().setRotHTarget(chara::ModelRotCtrl::ROT_H_TARGET);
        obj().model().model().nodes().at(6).localMtx().reset();
    }
    obj().objColl().clearAttack(1);
}

void StateCirclingFlight::procAnim() {
    const Param& param = obj().param().metalgeneral();
    if (Utility::IsVariationExtra(obj())) {
        mRot += param._18C;
        while (mRot > 360.0f) {
            mRot -= 360.0f;
        }
        obj().model().model().nodes().at(6).localMtx().setRTMtx(
            Matrix34::CreateRotXYZDeg(Vector3(0.0f, 0.0f, mRot))
        );
    }
}

void StateCirclingFlight::procMove() {
    const Param& param = obj().param().metalgeneral();
    obj().move().accel(mDir, param._158);
}

void StateCirclingFlight::procFixPos() {
    const Param& param = obj().param().metalgeneral();
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHitWallFront()) {
        Vector2 pos(param._190 * obj().target().getSign(), param._194);
        Vector2 speed(param._198 * obj().target().getSign(), param._19C);
        Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19A));
        obj().effect().normal().requestP(static_cast<effect::Kind>(0xB4), obj().location().pos() + pos.toVector3());
        obj().move().resetVelocity();
        obj().stateChanger().setNextState<StateCirclingFlightEnd, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::metalgeneral
