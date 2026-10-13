#include "scn/step/boss/hrd3/StatePressSearch.h"

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
#include "scn/step/boss/hrd3/StatePressFall.h"
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
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StatePressSearch::StatePressSearch(Boss* boss, u32 frame, u32 boundCount)
    : StateBase(boss), mCount(0), mFrame(frame), mBoundCount(boundCount), mStartX(boss->location().pos().x),
      mGoalPos(boss->location().pos()) {
    const Param& param = obj().param().hrd3();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.x = Utility::GetHatedHeroPos(obj()).x;
    mGoalPos.x = custom.landCtrl().getAdjustX(mGoalPos.x, param._C);
    mGoalPos.y = param._A0 + custom.landCtrl().getFloorY();
    mGoalPos.z = 0.0f;
    obj().model().reqScript(0x12);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().guard().setType(static_cast<GuardType>(2));
}

StatePressSearch::~StatePressSearch() {}

void StatePressSearch::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StatePressFall, Boss*, unsigned long>(objPtr(), mBoundCount);
    }
}

void StatePressSearch::procMove() {
    const Param& param = obj().param().hrd3();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);
    hel::math::Vector3 pos = obj().location().pos();
    pos.x = hel::math::Math::LinearInterpolation(mStartX, mGoalPos.x, rate);
    pos.y = hel::math::Math::LinearInterpolation(pos.y, mGoalPos.y, param._B4);
    pos.z = mGoalPos.z;
    obj().location().setPos(pos);
}

void StatePressSearch::procFixPos() {}

}
}
}
}
