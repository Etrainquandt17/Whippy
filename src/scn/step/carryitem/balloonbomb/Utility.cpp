#include "scn/step/carryitem/balloonbomb/Utility.h"

#include "hel/common/Color.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/Flash.h"
#include "scn/step/carryitem/balloonbomb/StateExplosion.h"
#include "scn/step/chara/Water.h"

namespace scn {
namespace step {
namespace carryitem {
namespace balloonbomb {

namespace {

// TODO: a guess: the original numbers the constant 64.0f ahead of 0.7f, as an argument of an inline function would be.
inline u8 t_base(f32 rate, f32 range) {
    u8 base = 0xA0;
    if (rate >= 0.7f) {
        base = 0xA0 + static_cast<int>(range * ((rate - 0.7f) / 0.3f));
    }
    return base;
}

}

bool Utility::IsDrop(CarryItem& carryItem) {
    return IsDanger(carryItem);
}

bool Utility::IsDanger(CarryItem& carryItem) {
    return carryItem.useCount() >= carryItem.param().balloonBomb()._50;
}

bool Utility::IsExplode(CarryItem& carryItem) {
    return carryItem.useCount() >= carryItem.param().balloonBomb()._54;
}

void Utility::UpdateFlash(CarryItem& carryItem, f32 wave) {
    u32 danger = carryItem.param().balloonBomb()._50;
    u32 explode = carryItem.param().balloonBomb()._54;
    f32 rate = static_cast<f32>(carryItem.useCount() - danger) / static_cast<f32>(explode - danger);
    if (wave < 0.0f) {
        wave = -wave;
    }
    u8 base = t_base(rate, 64.0f);
    u8 alpha = base - static_cast<int>(128.0f * (wave * (1.0f - rate)));
    carryItem.flash().set(hel::common::Color(0x80, 0x00, 0x00, alpha));
}

bool Utility::ChangeStateInWater(CarryItem* carryItem) {
    if (carryItem->water().isInWater()) {
        if (IsDanger(*carryItem)) {
            carryItem->stateChanger().setNextState<StateExplosion, CarryItem*>(carryItem);
        } else {
            carryItem->deadWithEffect();
        }
        return true;
    }
    return false;
}

}}}}  // namespace scn::step::carryitem::balloonbomb
