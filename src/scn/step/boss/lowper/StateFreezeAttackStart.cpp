#include "scn/step/boss/lowper/StateFreezeAttackStart.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateFreezeAttackHold.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"

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
