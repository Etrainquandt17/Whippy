#include "gfx/TPLTexture.h"

#include "revolution/gx/GXTexture.h"
#include "revolution/tpl.h"

namespace gfx {

void TextureObj::load(GXTexMapID id) const {
    GXLoadTexObj(&mTexObj, id);
}

GXTexObj TextureObj::texObj() const {
    return mTexObj;
}

TPLTexture::TPLTexture(const char* path)
    : mFile(path, false) {
    TPLPalette* palette = static_cast<TPLPalette*>(mFile.block().startAddress());
    if (reinterpret_cast<u32>(palette->descriptorArray) < 0x80000000) {
        TPLBind(palette);
    }
    TPLGetGXTexObjFromPalette(palette, &mTexObj, 0);
}

}
