#include "scn/step/boss/galactaknight/StateCameraOutWait.h"

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
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "scn/step/boss/galactaknight/StateWait.h"
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
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateCameraOutWait::StateCameraOutWait(Boss* boss, u32 frame, f32 height) : StateBase(boss), mFrame(frame), mCount(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Vector3 pos = obj().location().pos();
    f32 distance = 0.5f * custom.landCtrl().getWidth() + 2.0f;
    f32 center = custom.landCtrl().getCenterX();
    pos.x = distance * obj().target().getSign() + center;
    pos.y = height + custom.landCtrl().getFloorY();
    obj().location().setPos(pos);
    obj().target().invert();
    obj().model().reqScript(0);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().worldCage().setIsValid(false);
}

StateCameraOutWait::~StateCameraOutWait() {
    obj().worldCage().setIsValid(true);
}

void StateCameraOutWait::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        obj().brainCtrl().toValid();
    }
}

void StateCameraOutWait::procMove() {}

void StateCameraOutWait::procFixPos() {}

}}}}  // namespace scn::step::boss::galactaknight
