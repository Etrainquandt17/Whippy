extern "C" double fmod(double, double);

#include "scn/step/carryitem/cracker/Utility.h"

#include "g3d/ModelAnimAccessor.h"
#include "gobj/Anim.h"
#include "hel/common/Color.h"
#include "hel/math/Math.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/Flash.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace carryitem {
namespace cracker {

bool Utility::IsWarn(CarryItem& carryItem) {
    return carryItem.useCount() >= carryItem.param().cracker()._0;
}

bool Utility::IsDanger(CarryItem& carryItem) {
    return carryItem.useCount() >= carryItem.param().cracker()._4;
}

bool Utility::IsBroken(CarryItem& carryItem) {
    return carryItem.useCount() >= carryItem.param().cracker()._8;
}

f32 Utility::UpdateFlash(CarryItem& carryItem, f32 angle) {
    if (!IsDanger(carryItem)) {
        return angle;
    }
    const Param& param = carryItem.param().cracker();
    u32 danger = param._4;
    f32 rate = static_cast<f32>(carryItem.useCount() - danger) / static_cast<f32>(param._8 - danger);
    angle += IsBroken(carryItem) ? rate * param._34 : rate * param._30;
    angle = fmod(angle, 360.0);
    f32 cos = hel::math::Math::CosDegF(angle);
    u8 alpha = static_cast<u8>(144.0f * (0.5f * (1.0f - cos)));
    carryItem.flash().set(hel::common::Color(
        static_cast<u8>(128.0f + 127.0f * rate), static_cast<u8>(64.0f * (1.0f - rate)),
        static_cast<u8>(32.0f * (1.0f - rate)), alpha));
    return angle;
}

void Utility::StartSubAnim(CarryItem& carryItem, AnimKind kind) {
    carryItem.model().anim().subAnimSet(0, kind, 2);
    carryItem.model().anim().subAnimAccessor(0).start(true);
}

void Utility::ClearSubAnim(CarryItem& carryItem) {
    carryItem.model().anim().subAnimClear(0);
}

void Utility::StartFlashAnim(CarryItem& carryItem) {
    if (IsBroken(carryItem)) {
        return;
    }
    StartSubAnim(carryItem, IsDanger(carryItem) ? ANIM_KIND_RED : (IsWarn(carryItem) ? ANIM_KIND_YELLOW : ANIM_KIND_BLUE));
}

void Utility::UpdateFlashAnim(CarryItem& carryItem) {
    if (IsBroken(carryItem)) {
        return;
    }
    if (carryItem.useCount() == carryItem.param().cracker()._0) {
        StartSubAnim(carryItem, ANIM_KIND_YELLOW);
    } else if (carryItem.useCount() == carryItem.param().cracker()._4) {
        StartSubAnim(carryItem, ANIM_KIND_RED);
    }
}

}}}}  // namespace scn::step::carryitem::cracker
