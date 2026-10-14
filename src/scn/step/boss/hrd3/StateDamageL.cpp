#include "scn/step/boss/hrd3/StateDamageL.h"

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
#include "scn/step/boss/hrd3/StateAngerRise.h"
#include "scn/step/boss/hrd3/StateWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
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
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StateDamageL::StateDamageL(Boss* boss) : StateBase(boss), mCount(0), mWaitCount(0) {
    const Param& param = obj().param().hrd3();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::StagingBossDamageL(obj());
    obj().comp().enemyManager().reqDeadAllEnemyForBoss();
    obj().comp().weaponManager().reqDeadByTeamNo(ocoll::TEAM_NO_1);
    obj().model().rotCtrl().setRotHTargetDefault(50.0f);
    mStartPos = obj().location().pos();
    mGoalPos = mStartPos;
    mGoalPos.y = param._58 + custom.landCtrl().getFloorY();
    mGoalPos.z = -15.0f;
    obj().model().reqScript(6);
    custom.partsCtrl().deleteResidentEffect(PartsCtrl::RESIDENT_EFFECT_KIND_0);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_0);
    obj().comp().bgmController().pause(static_cast<core::BGMCategory>(1));
    obj().comp().bgmController().pause(core::BGM_CATEGORY_0);
    custom.partsCtrl().stopDrillSubAnim();
}

StateDamageL::~StateDamageL() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).partsCtrl().startDrillSubAnim();
}

void StateDamageL::procAnim() {
    const Param& param = obj().param().hrd3();
    if (mCount < param._50) {
        mCount++;
    } else if (mWaitCount < param._54) {
        mWaitCount++;
    } else {
        obj().stateChanger().setNextState<StateAngerRise, Boss*>(objPtr());
    }
}

void StateDamageL::procMove() {
    const Param& param = obj().param().hrd3();
    f32 rate;
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._50);
    f32 fall = 1.0f - Math::CosDegF(90.0f * t);
    rate = fall * fall;
    Vector3 pos;
    pos.x = Math::LinearInterpolation(mStartPos.x, mGoalPos.x, t);
    pos.y = Math::LinearInterpolation(mStartPos.y, mGoalPos.y, rate);
    pos.z = Math::LinearInterpolation(mStartPos.z, mGoalPos.z, t);
    obj().location().setPos(pos);
}

void StateDamageL::procFixPos() {}

}}}}  // namespace scn::step::boss::hrd3
