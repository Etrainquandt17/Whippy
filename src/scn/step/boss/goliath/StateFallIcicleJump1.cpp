#include "scn/step/boss/goliath/StateFallIcicleJump1.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "pow.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateFallIcicleJump2Start.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateFallIcicleJump1::StateFallIcicleJump1(Boss* boss, u32 time, u32 _2) : StateBase(boss), mFrame(0), mTime(time), _10(_2) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x25);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateFallIcicleJump1::~StateFallIcicleJump1() {}

void StateFallIcicleJump1::procAnim() {
    if (mFrame < mTime) {
        mFrame++;
    } else {
        obj().effect().normal().requestP(static_cast<effect::Kind>(0x28A), obj().location().pos(), 0.6f);
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
        obj().soundSE().normal().start(0x367);
        obj().stateChanger().setNextState<StateFallIcicleJump2Start, Boss*, u32, u32>(objPtr(), mTime, _10);
    }
}

void StateFallIcicleJump1::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(mTime);
    f32 height = 2.0f * (1.0f - POW3(1.0f - Math::SinDegF(180.0f * t)));
    Vector3 pos = obj().location().pos();
    pos.y = height + custom.landCtrl().getFloorYWithBump();
    obj().location().setPos(pos);
}

void StateFallIcicleJump1::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
