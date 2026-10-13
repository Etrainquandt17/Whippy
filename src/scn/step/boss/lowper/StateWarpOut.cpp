#include "scn/step/boss/lowper/StateWarpOut.h"

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

StateWarpOut::StateWarpOut(Boss* boss, const hel::math::Vector3& pos) : StateBase(boss), mCount(0) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_0);
    obj().model().reqScript(0x19);
    hel::geo::Rect rect = obj().comp().mainCamera().getViewRect();
    f32 width = hel::math::Math::AbsF32(rect._C - rect._8);
    hel::math::Vector3 offset = pos;
    offset.x = hel::math::Math::Limit(offset.x, 0.5f * width - 1.5f);
    custom.waftMoveCtrl().setCenter(obj().basePos().toVector3() + offset);
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    obj().model().setScale(hel::math::Vector3(0.01f, 2.0f, 0.01f));
    obj().location().setPos(obj().basePos().toVector3() + offset);
    f32 baseX = obj().basePos().x;
    obj().target().setIsRightDir(obj().location().pos().x < baseX);
}

StateWarpOut::~StateWarpOut() {
    obj().model().setVisibility(true);
    obj().model().resetScale();
}

void StateWarpOut::procAnim() {
    mCount++;
    if (mCount < 40) {
        mCount++;
        if (mCount == 40) {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
            return;
        }
    }
    f32 t = static_cast<f32>(mCount) / 40.0f;
    hel::math::Vector3 scale(t, (1.0f - t) * (1.0f - t) + 1.0f, t);
    obj().model().setScale(scale);
}

void StateWarpOut::procMove() {}

void StateWarpOut::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
