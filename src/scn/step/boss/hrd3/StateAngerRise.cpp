#include "scn/step/boss/hrd3/StateAngerRise.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/BGMCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/InfoHitPointCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/hrd3/CollisionCtrl.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/LandCtrl.h"
#include "scn/step/boss/hrd3/Param.h"
#include "scn/step/boss/hrd3/PartsCtrl.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/info/BossPanel.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StateAngerRise::StateAngerRise(Boss* boss)
    : StateBase(boss), mCount(0), mFrame(boss->param().hrd3()._9C), mStartPos(boss->location().pos()), mGoalY(0.0f),
      mIsMove(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mStartPos.x = custom.landCtrl().getCenterX();
    obj().location().setPos(mStartPos);
    mGoalY = obj().param().hrd3()._A4 + custom.landCtrl().getFloorY();
    obj().model().reqScript(7);
    custom.partsCtrl().addResidentEffect(PartsCtrl::RESIDENT_EFFECT_KIND_0);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().guard().setType(static_cast<GuardType>(1));
    obj().hitPoint().resetMin();
    obj().infoHitPointCtrl().unsetZero();
    obj().infoHitPointCtrl().setFull(obj().hitPoint().get());
    obj().infoBossPanel().heal(obj().infoHitPointCtrl().getHitPointRate());
    obj().infoBossPanel().transformStart();
    obj().bgmCtrl().startBossBattleHRD3Phase2();
}

StateAngerRise::~StateAngerRise() {
    obj().infoBossPanel().transformEnd();
}

void StateAngerRise::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        mIsMove = true;
    }
    if (mIsMove) {
        if (mCount < mFrame) {
            mCount++;
        } else {
            obj().brainCtrl().toValid();
        }
    }
}

void StateAngerRise::procMove() {
    if (mIsMove) {
        f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
        f32 rate = 1.0f - Math::CosDegF(90.0f * t);
        f32 rateSquare = rate * rate;
        f32 easing = Math::LinearInterpolation(rate, rateSquare, 0.5f);
        Vector3 pos = mStartPos;
        pos.y = Math::LinearInterpolation(mStartPos.y, mGoalY, easing);
        obj().location().setPos(pos);
    }
}

void StateAngerRise::procFixPos() {}

}}}}  // namespace scn::step::boss::hrd3
