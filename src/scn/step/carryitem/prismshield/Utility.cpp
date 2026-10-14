#include "scn/step/carryitem/prismshield/Utility.h"

#include "g3d/ModelAnimAccessor.h"
#include "gobj/Anim.h"
#include "hel/common/Color.h"
#include "hel/math/Math.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/Flash.h"
#include "scn/step/chara/Model.h"

using hel::common::Color;
using hel::math::Math;

namespace scn {
namespace step {
namespace carryitem {
namespace prismshield {

bool Utility::IsWarn(CarryItem& carryItem) {
    return carryItem.useCount() >= carryItem.param().prismShield()._0;
}

bool Utility::IsDanger(CarryItem& carryItem) {
    return carryItem.useCount() >= carryItem.param().prismShield()._4;
}

void Utility::StartAnim(CarryItem& carryItem, AnimKind kind) {
    carryItem.model().anim().subAnimSet(0, kind, 1);
    carryItem.model().anim().subAnimAccessor(0).start(true);
}

void Utility::StartFlash(CarryItem& carryItem) {
    StartAnim(carryItem, IsDanger(carryItem) ? ANIM_KIND_RED : (IsWarn(carryItem) ? ANIM_KIND_YELLOW : ANIM_KIND_BLUE));
}

void Utility::UpdateFlash(CarryItem& carryItem) {
    if (carryItem.useCount() == carryItem.param().prismShield()._0) {
        StartAnim(carryItem, ANIM_KIND_YELLOW);
    } else if (carryItem.useCount() == carryItem.param().prismShield()._4) {
        StartAnim(carryItem, ANIM_KIND_RED);
    }
}

// TODO: r29 and r30 are swapped: the original keeps the parameters in r30 and the first threshold in r29.
f32 Utility::UpdateFlash(CarryItem& carryItem, f32 angle) {
    if (!IsDanger(carryItem) && !IsWarn(carryItem)) {
        return angle;
    }
    f32 wave;
    f32 rate;
    u32 base;
    const Param& param = carryItem.param().prismShield();
    base = param._0;
    rate = (static_cast<f32>(carryItem.useCount()) - static_cast<f32>(base))
           / (static_cast<f32>(param._8) - static_cast<f32>(base));
    if (IsDanger(carryItem)) {
        angle += param._14 * rate;
    } else if (IsWarn(carryItem)) {
        angle += param._10;
    }
    wave = 0.5f * Math::SinDegF(angle) + 0.5f;
    base = static_cast<u8>(param._20);
    u8 alpha = base - static_cast<int>(static_cast<f32>(param._28) * wave);
    if (IsDanger(carryItem) && rate >= 0.7f) {
        base += static_cast<int>((rate - 0.7f) / 0.3f * static_cast<f32>(param._24));
        alpha = base - static_cast<int>((1.5f - rate) * (static_cast<f32>(param._28) * wave));
    }
    carryItem.flash().set(Color(0xFF, 0x10, 0x00, alpha));
    return angle;
}

}}}}  // namespace scn::step::carryitem::prismshield
