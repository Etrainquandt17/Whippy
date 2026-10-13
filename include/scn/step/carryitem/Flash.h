#ifndef SCN_STEP_CARRYITEM_FLASH_H
#define SCN_STEP_CARRYITEM_FLASH_H

#include "gobj/ColorAnim.h"

namespace scn {
namespace step {
namespace carryitem {

class CarryItem;

class Flash {
public:
    Flash(CarryItem& carryItem, mem::IAllocator& allocator);

    void update();
    void updateUseGPU();
    void set(const GXColor& color);
    void unset();

private:
    CarryItem& mObj;
    gobj::ColorAnim mColorAnim;
    GXColor mColor;
};

}}}  // namespace scn::step::carryitem

#endif
