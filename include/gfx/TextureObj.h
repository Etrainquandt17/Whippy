#ifndef GFX_TEXTUREOBJ_H
#define GFX_TEXTUREOBJ_H

#include "revolution/gx/GXEnum.h"
#include "revolution/gx/GXStruct.h"

namespace gfx {

class TextureObj {
public:
    virtual ~TextureObj() {}

    void load(GXTexMapID id) const;
    GXTexObj texObj() const;

protected:
    GXTexObj mTexObj;
};

}  // namespace gfx

#endif
