#include "scn/step/carryitem/candle/Utility.h"

#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Water.h"

namespace scn {
namespace step {
namespace carryitem {
namespace candle {

void Utility::ChkWater(CarryItem& carryItem) {
    if (carryItem.useCount() == 0 && carryItem.water().isInWater()) {
        carryItem.effectBack().release();
        carryItem.setUseCount(1);
    }
}

}}}}  // namespace scn::step::carryitem::candle
