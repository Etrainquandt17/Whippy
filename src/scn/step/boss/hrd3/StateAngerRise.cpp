#include "scn/step/boss/hrd3/StateAngerRise.h"

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
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/info/BossPanel.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StateAngerRise::StateAngerRise(Boss* boss)
    : StateBase(boss), mCount(0), mFrame(boss->param().hrd3()._9C), mStartPos(boss->location().pos()), mGoalY(0.0f),
      mIsMove(false) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
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
        f32 rate = 1.0f - hel::math::Math::CosDegF(90.0f * t);
        f32 rateSquare = rate * rate;
        f32 easing = hel::math::Math::LinearInterpolation(rate, rateSquare, 0.5f);
        hel::math::Vector3 pos = mStartPos;
        pos.y = hel::math::Math::LinearInterpolation(mStartPos.y, mGoalY, easing);
        obj().location().setPos(pos);
    }
}

void StateAngerRise::procFixPos() {}

}
}
}
}
