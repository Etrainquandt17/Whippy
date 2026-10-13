#include "scn/step/boss/lowper/StateTackleGlide.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
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

StateTackleGlide::StateTackleGlide(Boss* boss, u32 frame)
    : StateBase(boss), mCount(0), mFrame(frame), mStartY(0.0f), mGoalY(0.0f), mGoalX(0.0f), mStartX(0.0f) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().lowper();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    f32 baseX = obj().basePos().x;
    f32 sign = hel::math::Math::SignF32(obj().location().pos().x - baseX);
    mStartY = obj().comp().mainCamera().getWorldRect()._0 - param._2C;
    mGoalY = param._28 + obj().basePos().y;
    mGoalX = obj().basePos().x + 0.5f * sign * param._24;
    mStartX = obj().basePos().x - 0.5f * sign * param._24;
    obj().model().reqScript(0xA);
}

StateTackleGlide::~StateTackleGlide() {}

void StateTackleGlide::procAnim() {
    mCount++;
    if (mCount == mFrame) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateTackleGlide::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    hel::math::Vector2 pos;
    f32 cos = hel::math::Math::CosDegF(180.0f * t);
    f32 rateX = 0.5f * (1.0f + cos);
    pos.x = hel::math::Math::LinearInterpolation(mStartX, mGoalX, rateX);
    f32 sin = hel::math::Math::SinDegF(180.0f * t);
    f32 rateY = 1.0f - sin;
    pos.y = hel::math::Math::LinearInterpolation(mGoalY, mStartY, rateY);
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().lowper();
    custom.waftMoveCtrl().setMoveIntpRate(param._30);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos.toVector3());
}

void StateTackleGlide::procFixPos() {}

}
}
}
}
