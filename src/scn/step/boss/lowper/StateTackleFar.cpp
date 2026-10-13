#include "scn/step/boss/lowper/StateTackleFar.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/DataBuff.h"
#include "scn/step/boss/lowper/EnemyCtrl.h"
#include "scn/step/boss/lowper/GearCtrl.h"
#include "scn/step/boss/lowper/ItemCtrl.h"
#include "scn/step/boss/lowper/MiniBlackHoleCtrl.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/boss/lowper/WaftMoveCtrl.h"
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
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateTackleFar::StateTackleFar(Boss* boss)
    : StateBase(boss), mCount(0), mSwayCount(0), mStartY(0.0f), mGoalY(0.0f), mX(0.0f), mSway(0.0f) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().lowper();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_3);
    mStartY = 4.0f + obj().basePos().y;
    mGoalY = param._44 + obj().basePos().y;
    mX = obj().location().pos().x;
    mSway = param._4C;
    obj().model().reqScript(0xB);
    obj().model().rotCtrl().setRotHTarget(0.0f);
}

StateTackleFar::~StateTackleFar() {}

void StateTackleFar::procAnim() {
    const Param& param = obj().param().lowper();
    mSwayCount++;
    if (mSwayCount == param._48) {
        mSwayCount = 0;
        mSway *= -1.0f;
    }
    mCount++;
    if (mCount == param._40) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateTackleFar::procMove() {
    const Param& param = obj().param().lowper();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._40);
    hel::math::Vector3 pos;
    pos.x = mX + mSway;
    f32 sin = hel::math::Math::SinDegF(180.0f * t);
    f32 rate = 1.0f - sin;
    if (t > 0.5f) {
        rate *= 0.5f;
    }
    pos.y = hel::math::Math::Interpolate(mGoalY, mStartY, rate);
    pos.z = -80.0f * (1.0f - t) + 80.0f * t;
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
}

void StateTackleFar::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
