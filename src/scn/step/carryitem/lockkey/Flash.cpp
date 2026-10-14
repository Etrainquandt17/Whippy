#include "scn/step/carryitem/lockkey/Flash.h"

#include "hel/common/Color.h"
#include "hel/math/Math.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/Flash.h"
#include "scn/step/carryitem/lockkey/Utility.h"

using hel::common::Color;
using hel::math::Math;

namespace scn {
namespace step {
namespace carryitem {
namespace lockkey {

Flash::Flash(CarryItem& carryItem)
    : mObj(carryItem)
    , mAngle(0.0f)
    , mInterval(0) {}

void Flash::update() {
    if (!Utility::IsDanger(mObj)) {
        return;
    }
    if (mInterval != 0) {
        updateInterval();
    } else {
        updateFlash();
        mInterval = mObj.param().lockKey()._1C;
        return;
    }
    if (isFlash()) {
        updateFlash();
    }
}

void Flash::updateInterval() {
    u32 dec = static_cast<u32>(ratio() * static_cast<f32>(mObj.param().lockKey()._20));
    if (dec == 0) {
        dec = 1;
    }
    if (mInterval < dec) {
        mInterval = 0;
    } else {
        mInterval -= dec;
    }
}

bool Flash::isFlash() {
    return 0.0f != mAngle;
}

void Flash::updateFlash() {
    const Param& param = mObj.param().lockKey();
    if (!Utility::IsDanger(mObj)) {
        mAngle = 0.0f;
        return;
    }
    mAngle += ratio() >= param._14 ? param._10 : param._C;
    if (mAngle >= 180.0f) {
        mAngle = 0.0f;
    }
    mObj.flash().set(Color(0xFF, 0x10, 0x00, static_cast<u8>(static_cast<f32>(param._18) * Math::SinDegF(mAngle))));
}

f32 Flash::ratio() {
    const Param& param = mObj.param().lockKey();
    u32 start = param._0 - param._8;
    f32 t = (static_cast<f32>(mObj.useCount()) - static_cast<f32>(start)) / (static_cast<f32>(param._4) - static_cast<f32>(param._0));
    return Math::Min(t * t, 1.0f);
}

}}}}  // namespace scn::step::carryitem::lockkey
