#ifndef GFX_TPLTEXTUREPLATE_H
#define GFX_TPLTEXTUREPLATE_H

#include "gfx/TPLTexture.h"
#include "nw4r/ut/ut_Rect.h"
#include "revolution/gx/GXStruct.h"
#include "revolution/mtx.h"
#include "types.h"

namespace hel {
namespace math {
class Vector2;
}}  // namespace hel::math

namespace gfx {

class TPLTexturePlate {
public:
    TPLTexturePlate(const char* path);

    void setAlpha(u8 alpha);
    void drawForHomeButtonIcon() const;
    void setPos(const hel::math::Vector2& pos);

private:
    void drawCore() const;
    void setupTevRenderModePlane() const;

    TPLTexture mTexture;
    GXTexObj mTexObj;
    nw4r::ut::Rect mRect;
    Mtx mPos;
    u8 mAlpha;
    bool mIsInitialized;
};

}  // namespace gfx

#endif
