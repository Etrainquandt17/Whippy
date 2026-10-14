#include "scn/step/boss/lowper/StateMove.h"

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

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateMove::StateMove(Boss* boss, const Vector3& pos, u32 frame)
    : StateBase(boss), mStartPos(), mGoalPos(), mCount(0), mFrame(frame) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().lowper();
    mStartPos = custom.waftMoveCtrl().getCenter();
    mGoalPos = obj().basePos().toVector3() + pos;
    if (mStartPos.z > 10.0f) {
        f32 centerX = obj().comp().mainCamera().getCenter().x;
        if (mGoalPos.x > centerX) {
            mStartPos.x = Math::LimitMin(mStartPos.x, 1.0f + centerX);
        } else {
            mStartPos.x = Math::LimitMax(mStartPos.x, centerX - 1.0f);
        }
    }
    custom.waftMoveCtrl().setMoveIntpRate(param._20);
    custom.waftMoveCtrl().setWaveWidth(param._1C);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().model().reqScript(0);
}

StateMove::~StateMove() {}

void StateMove::procAnim() {
    if (++mCount >= mFrame) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateMove::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 rate = 0.5f * (1.0f + Math::CosDegF(180.0f * t));
    custom.waftMoveCtrl().setCenter(Math::LinearInterpolation(mGoalPos, mStartPos, rate));
}

void StateMove::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
