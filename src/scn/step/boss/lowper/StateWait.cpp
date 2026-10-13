#include "scn/step/boss/lowper/StateWait.h"

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

StateWait::StateWait(Boss* boss) : StateBase(boss) {
    commonInit(hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).waftMoveCtrl().getCenter());
}

StateWait::StateWait(Boss* boss, const hel::math::Vector3& offset) : StateBase(boss) {
    commonInit(obj().basePos().toVector3() + offset);
}

StateWait::~StateWait() {}

void StateWait::procAnim() {}

void StateWait::procMove() {}

void StateWait::procFixPos() {
    f32 baseX = obj().basePos().x;
    bool isRight = obj().location().pos().x < baseX;
    obj().target().setIsRightDir(isRight);
}

void StateWait::commonInit(const hel::math::Vector3& pos) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().lowper();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().brainCtrl().toValid();
    obj().model().reqScript(0);
    obj().hateCtrl().fix();
    custom.waftMoveCtrl().setCenter(pos);
    custom.waftMoveCtrl().setMoveIntpRate(param._18);
    custom.waftMoveCtrl().setWaveWidth(param._14);
}

}}}}  // namespace scn::step::boss::lowper
