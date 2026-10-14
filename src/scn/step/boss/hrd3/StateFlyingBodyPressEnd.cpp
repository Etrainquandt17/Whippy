#include "scn/step/boss/hrd3/StateFlyingBodyPressEnd.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/BGMCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/InfoHitPointCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/hrd3/CollisionCtrl.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/LandCtrl.h"
#include "scn/step/boss/hrd3/Param.h"
#include "scn/step/boss/hrd3/PartsCtrl.h"
#include "scn/step/boss/hrd3/PilotCtrl.h"
#include "scn/step/boss/hrd3/ShadowCtrl.h"
#include "scn/step/boss/hrd3/StateWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/core/BGMController.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/info/BossPanel.h"
#include "scn/step/weapon/Manager.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StateFlyingBodyPressEnd::StateFlyingBodyPressEnd(Boss* boss)
    : StateBase(boss), mCount(0), mStartPos(boss->location().pos()), mGoalY(0.0f), mIsMove(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalY = custom.landCtrl().getFloorY();
    obj().model().reqScript(0x1D);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    reqStar();
    obj().guard().setType(static_cast<GuardType>(2));
}

StateFlyingBodyPressEnd::~StateFlyingBodyPressEnd() {}

void StateFlyingBodyPressEnd::procAnim() {
    const Param& param = obj().param().hrd3();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        mIsMove = true;
    }
    if (mIsMove) {
        if (mCount < param._EC) {
            mCount++;
        } else {
            if (obj().model().isAllEnd()) {
                obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
            }
            return;
        }
    }
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._EC);
    f32 rot = 1.0f - Math::SinDegF(90.0f * t);
    rot *= -custom.partsCtrl().getMaxRotV() * obj().target().getSign();
    obj().model().rotCtrl().initRotV(rot);
}

void StateFlyingBodyPressEnd::procMove() {
    if (mIsMove) {
        const Param& param = obj().param().hrd3();
        f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._EC);
        f32 rate = Math::SinDegF(90.0f * t);
        Vector3 pos = mStartPos;
        pos.y = Math::LinearInterpolation(mStartPos.y, mGoalY, rate);
        f32 slide = param._DC * -obj().target().getSign();
        pos.x += Math::LinearInterpolation(0.0f, slide, rate);
        obj().location().setPos(pos);
    }
}

void StateFlyingBodyPressEnd::procFixPos() {}

void StateFlyingBodyPressEnd::reqStar() {
    const Param& param = obj().param().hrd3();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Vector2 pos = obj().location().pos().getXY();
    pos.y = custom.landCtrl().getFloorY();
    Vector2 speed(param._F0, 0.0f);
    Vector2 accel(param._F4, param._1C.y);
    Utility::GenerateStarEffect(obj(), pos, speed, accel, static_cast<map::BinEnemyVariation>(0x19B));
    speed.x *= -1.0f;
    accel.x *= -1.0f;
    Utility::GenerateStarEffect(obj(), pos, speed, accel, static_cast<map::BinEnemyVariation>(0x19B));
}

}}}}  // namespace scn::step::boss::hrd3
