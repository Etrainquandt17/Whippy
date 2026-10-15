#include "scn/step/boss/goliath/StateFallIcicleBigJump.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "pow.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateFallIcicleBigLanding.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateFallIcicleBigJump::StateFallIcicleBigJump(Boss* boss, u32 time) : StateBase(boss), mFrame(0), mTime(time) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x29);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateFallIcicleBigJump::~StateFallIcicleBigJump() {}

void StateFallIcicleBigJump::procAnim() {
    if (mFrame < mTime) {
        mFrame++;
    } else {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).icicleCtrl().fall();
        obj().stateChanger().setNextState<StateFallIcicleBigLanding, Boss*>(objPtr());
    }
}

void StateFallIcicleBigJump::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(mTime);
    f32 height = 6.0f * (1.0f - POW3(1.0f - Math::SinDegF(180.0f * t)));
    Vector3 pos = obj().location().pos();
    pos.y = height + custom.landCtrl().getFloorYWithBump();
    obj().location().setPos(pos);
}

void StateFallIcicleBigJump::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
