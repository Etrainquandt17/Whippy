#include "scn/step/carryitem/Flash.h"

#include "gobj/GearModel.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace carryitem {

namespace {

const GXColor T_UNSET_COLOR = { 0xFF, 0xFF, 0xFF, 0x00 };

}

Flash::Flash(CarryItem& carryItem, mem::IAllocator& allocator)
    : mObj(carryItem)
    // TODO: gobj::GearModel is a gobj::IG3DModel; its header does not say so yet.
    , mColorAnim(gobj::ColorAnimDesc(), allocator, *reinterpret_cast<gobj::IG3DModel*>(&carryItem.model().model()))
    , mColor(T_UNSET_COLOR) {}

void Flash::update() {
    g3d::ColorAnimFlash flash = mColorAnim.flash();
    flash.setColor(mColor);
    mColorAnim.setFlash(flash);
}

void Flash::updateUseGPU() {
    mColorAnim.updateUseGPU();
}

void Flash::set(const GXColor& color) {
    mColor = color;
}

void Flash::unset() {
    mColor = T_UNSET_COLOR;
}

}}}  // namespace scn::step::carryitem
