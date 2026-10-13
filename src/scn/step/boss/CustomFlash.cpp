#include "scn/step/boss/CustomFlash.h"

namespace scn {
namespace step {
namespace boss {

CustomFlash::CustomFlash() : mColor((GXColor){ 0, 0, 0, 0 }), mOperation(g3d::ColorAnimFlashOp_0), mIsValid(false) {}

void CustomFlash::update() {}

void CustomFlash::setIsValid(bool isValid) {
    mIsValid = isValid;
    if (!mIsValid) {
        GXColor color = { 0, 0, 0, 0 };
        mColor = color;
        mOperation = g3d::ColorAnimFlashOp_0;
    }
}

bool CustomFlash::isValid() const {
    return mIsValid;
}

void CustomFlash::setColor(const GXColor& color) {
    mColor = color;
}

void CustomFlash::setOperation(g3d::ColorAnimFlashOp op) {
    mOperation = op;
}

GXColor CustomFlash::getColor() const {
    return mColor;
}

g3d::ColorAnimFlashOp CustomFlash::getOperation() const {
    return mOperation;
}

}
}
}
