#include "scn/step/boss/galactaknight/StateCameraOutWait.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/WorldCage.h"

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
