#include "scn/step/boss/CustomFlash.h"

using g3d::ColorAnimFlashOp;
using g3d::ColorAnimFlashOp_0;

namespace scn {
namespace step {
namespace boss {

CustomFlash::CustomFlash() : mColor((GXColor){ 0, 0, 0, 0 }), mOperation(ColorAnimFlashOp_0), mIsValid(false) {}

void CustomFlash::update() {}

void CustomFlash::setIsValid(bool isValid) {
    mIsValid = isValid;
    if (!mIsValid) {
        GXColor color = { 0, 0, 0, 0 };
        mColor = color;
        mOperation = ColorAnimFlashOp_0;
    }
}

bool CustomFlash::isValid() const {
    return mIsValid;
}

void CustomFlash::setColor(const GXColor& color) {
    mColor = color;
}

void CustomFlash::setOperation(ColorAnimFlashOp op) {
    mOperation = op;
}

GXColor CustomFlash::getColor() const {
    return mColor;
}

ColorAnimFlashOp CustomFlash::getOperation() const {
    return mOperation;
}

}}}  // namespace scn::step::boss
