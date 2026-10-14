#ifndef SCN_STEP_CARRYITEM_LOCKKEY_FLASH_H
#define SCN_STEP_CARRYITEM_LOCKKEY_FLASH_H

#include "scn/step/carryitem/CarryItem.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {
namespace lockkey {

class Flash {
public:
    Flash(CarryItem& carryItem);

    void update();
    void updateInterval();
    bool isFlash();
    void updateFlash();
    f32 ratio();

private:
    CarryItem& mObj;
    f32 mAngle;
    u32 mInterval;
};

}}}}  // namespace scn::step::carryitem::lockkey

#endif
