#include "scn/step/boss/lowper/StateFreezeAttackStart.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
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
#include "scn/step/boss/lowper/StateFreezeAttackHold.h"
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

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateFreezeAttackStart::StateFreezeAttackStart(Boss* boss, u32 _2, u32 _3, u32 _4)
    : StateBase(boss), _8(_2), _C(_3), _10(_4), mCount(0), mDir(Vector3::BASIS_Y), mSpeed(0.0f) {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Utility::ControlHateOnAction(obj());
    Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    Vector3 diff = heroPos - obj().location().pos();
    if (!diff.isZeroLoose(0.00001f)) {
        mDir = diff.getNormalized();
    }
    obj().model().reqScript(0x1F);
    obj().model().rotCtrl().setRotHTarget(0.0f);
    obj().guard().setType(static_cast<GuardType>(4));
}

StateFreezeAttackStart::~StateFreezeAttackStart() {
    obj().objColl().clearAttack(1);
    obj().model().model().nodes().at(3).localMtx().reset();
}

void StateFreezeAttackStart::procAnim() {
    if (mCount < _8 + _C) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateFreezeAttackHold, Boss*, unsigned long>(objPtr(), _10);
    }
}

void StateFreezeAttackStart::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(_8 + _C);
    f32 rate = 1.0f - (1.0f - Math::CosDegF(90.0f * t)) *
                          ((1.0f - Math::CosDegF(90.0f * t)) * (1.0f - Math::CosDegF(90.0f * t)));
    Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    Vector3 diff = heroPos - obj().location().pos();
    if (diff.length() > 1.0f) {
        mDir = diff.getNormalized();
    }
    Vector3 center = custom.waftMoveCtrl().getCenter();
    center += mDir * mSpeed * rate;
    if (mCount >= _8) {
        mSpeed += 0.00075f;
        if (mSpeed > 0.045f) {
            mSpeed = 0.045f;
        }
    }
    custom.waftMoveCtrl().setMoveIntpRate(0.5f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(center);
}

void StateFreezeAttackStart::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
