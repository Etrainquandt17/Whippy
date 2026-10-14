#include "scn/step/carryitem/stepshoe/Utility.h"

#include "gobj/Anim.h"
#include "hel/common/Color.h"
#include "hel/math/Math.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/Flash.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"

using hel::common::Color;
using hel::math::Math;

namespace scn {
namespace step {
namespace carryitem {
namespace stepshoe {

bool Utility::IsWarn(CarryItem& carryItem) {
    return carryItem.useCount() >= carryItem.param().stepShoe()._14;
}

bool Utility::IsDanger(CarryItem& carryItem) {
    return carryItem.useCount() >= carryItem.param().stepShoe()._18;
}

bool Utility::ChkLifeTime(CarryItem& carryItem) {
    if (!carryItem.getUser().wasSet()) {
        return false;
    }
    if (carryItem.getUser()->isBackDir()) {
        return false;
    }
    carryItem.incUseCount();
    if (carryItem.useCount() >= carryItem.param().stepShoe()._1C) {
        carryItem.deadWithEffect();
        return true;
    }
    return false;
}

void Utility::SetFlash(CarryItem& carryItem) {
    const Param& param = carryItem.param().stepShoe();
    u32 count = carryItem.useCount();
    bool isWarn = count >= param._14;
    bool isDanger = count >= param._18;
    bool isChange = count == 0 || count == param._14 || count == param._18;
    if (isChange) {
        u32 anim = 9;
        if (isDanger) {
            anim = 0xB;
        } else if (isWarn) {
            anim = 0xA;
        }
        carryItem.model().anim().subAnimSet(0, anim, 3);
        carryItem.model().anim().subAnimAccessor(0).start(true);
    }
}

void Utility::ReqFlashEffect(CarryItem& carryItem) {
    const Param& param = carryItem.param().stepShoe();
    if (carryItem.useCount() >= param._18) {
        if (carryItem.model().anim().subAnimAccessor(0).isValid()) {
            if (8.0f == carryItem.model().anim().subAnimAccessor(0).frame()) {
                carryItem.effect().requestN(static_cast<effect::Kind>(0x359), 4);
            }
        }
    }
}

f32 Utility::UpdateBodyFlash(CarryItem& carryItem, f32 angle) {
    const Param& param = carryItem.param().stepShoe();
    u32 count = carryItem.useCount();
    if (!IsWarn(carryItem)) {
        return angle;
    }
    if (count == param._18) {
        angle = 180.0f;
    } else {
        angle += param._2C;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
    }
    f32 rate = 0.5f * Math::SinDegF(angle) + 0.5f;
    u8 alpha = static_cast<u8>(128.0f * rate);
    carryItem.flash().set(Color(0xFF, 0x10, 0x00, alpha));
    return angle;
}

}}}}  // namespace scn::step::carryitem::stepshoe
