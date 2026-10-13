#include "scn/step/boss/hrd3/StateFlyingBodyPressFall.h"

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
#include "scn/step/boss/hrd3/StateFlyingBodyPressEnd.h"
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

StateFlyingBodyPressFall::StateFlyingBodyPressFall(Boss* boss)
    : StateBase(boss), mCount(0), mStartPos(boss->location().pos()) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x1C);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().guard().setType(static_cast<GuardType>(2));
    f32 rot = -custom.partsCtrl().getMaxRotV() * obj().target().getSign();
    obj().model().rotCtrl().initRotV(rot);
}

StateFlyingBodyPressFall::~StateFlyingBodyPressFall() {}

void StateFlyingBodyPressFall::procAnim() {
    const Param& param = obj().param().hrd3();
    if (mCount < param._E4) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateFlyingBodyPressEnd, Boss*>(objPtr());
    }
}

void StateFlyingBodyPressFall::procMove() {
    const Param& param = obj().param().hrd3();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._E4);
    f32 rate = 1.0f - hel::math::Math::CosDegF(90.0f * t);
    f32 goalY = custom.partsCtrl().getFallOverHeightOffset() + custom.landCtrl().getFloorY();
    hel::math::Vector3 pos = mStartPos;
    pos.y = hel::math::Math::LinearInterpolation(mStartPos.y, goalY, rate);
    obj().location().setPos(pos);
}

void StateFlyingBodyPressFall::procFixPos() {}

}}}}  // namespace scn::step::boss::hrd3
