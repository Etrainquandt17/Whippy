#include "scn/step/boss/goliath/StatePunchCharge.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/boss/goliath/StatePunch.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StatePunchCharge::StatePunchCharge(Boss* boss, u32 _1, u32 _2, bool _3) : StateBase(boss), _8(_1), _C(_2), _10(_3) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(7);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(GUARD_TYPE_1);
}

StatePunchCharge::~StatePunchCharge() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).elevationCtrl().resetElev();
}

void StatePunchCharge::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (_8 != 0) {
        _8--;
        if (_8 == 0) {
            obj().flash().attack().setStart((GXColor){ 0xFF, 0xFF, 0xFF, 0x80 });
        }
    } else if (_C != 0) {
        _C--;
    } else {
        obj().stateChanger().setNextState<StatePunch, Boss*, f32, bool>(objPtr(), custom.elevationCtrl().getElevX(), _10);
        return;
    }
    if (_8 != 0) {
        Vector3 pos = obj().location().pos();
        Vector3 heroPos = Utility::GetHatedHeroPos(obj());
        f32 angle = 90.0f - Math::Atan2DegF(Math::AbsF32(heroPos.x - pos.x), heroPos.y - pos.y);
        custom.elevationCtrl().setElevX(Math::LimitMax(angle, obj().param().goliath()._88));
    }
}

void StatePunchCharge::procMove() {}

void StatePunchCharge::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
