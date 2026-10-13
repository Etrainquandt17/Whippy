#include "gfx/FullScreenPlate.h"

#include "gfx/Utility.h"
#include "nrel/ezrender/Render2D.h"
#include "nw4r/ut/ut_Rect.h"

namespace gfx {

FullScreenPlate::FullScreenPlate(const GXColor& color)
    : mColor(color)
    , mAlpha(1.0f) {}

void FullScreenPlate::draw() const {
    Utility::SetupGXForScreen2D(0.0f, 1.0f);
    f32 width = Utility::CurrentGameWidth();
    f32 height = Utility::CurrentGameHeight();
    GXColor color = mColor;
    color.a = mColor.a * mAlpha;
    nrel::ezrender::Render2D::renderRect(nw4r::ut::Rect(0.0f, 0.0f, width, height), color);
}

void FullScreenPlate::setColor(const GXColor& color) {
    mColor = color;
}

void FullScreenPlate::setAlpha(f32 alpha) {
    mAlpha = alpha;
}

}  // namespace gfx
