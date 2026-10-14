#include "scn/step/boss/lowper/StateMoveToOtherSide.h"

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

using app::Random;
using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

namespace {

const f32 ZPosTable[] = { 0.0f, -35.0f, 0.0f, -35.0f, 10.0f };
const u32 WaitFrameTable[] = { 10, 5, 50, 10, 5 };

}

StateMoveToOtherSide::StateMoveToOtherSide(Boss* boss) : StateBase(boss), mPositions(), mCount(0), mIndex(0) {
    obj().model().reqScript(0);
    f32 baseX = obj().basePos().x;
    f32 sign = obj().location().pos().x > baseX ? 1.0f : -1.0f;
    Vector3 startPos = obj().location().pos();
    Vector3 goalPos(obj().basePos().x - 5.0f * sign, 4.0f + obj().basePos().y, 0.0f);
    f32 side = -1.0f;
    for (u32 i = 0; i < 5; i++) {
        f32 t = static_cast<f32>(i + 1) / 6.0f;
        Vector3 pos = startPos * (1.0f - t) + goalPos * t;
        pos.y += side * (0.5f * Random::RandNF() + 0.5f);
        pos.z = ZPosTable[i];
        mPositions.add(pos);
        side *= -1.0f;
    }
}

StateMoveToOtherSide::~StateMoveToOtherSide() {
    mPositions.clear();
}

void StateMoveToOtherSide::procAnim() {
    mCount++;
    if (mCount >= WaitFrameTable[mIndex]) {
        mCount = 0;
        mIndex++;
        if (mIndex >= 5) {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        }
    }
}

void StateMoveToOtherSide::procMove() {
    Vector3 pos = mPositions[mIndex];
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.waftMoveCtrl().setMoveIntpRate(0.5f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
}

void StateMoveToOtherSide::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
