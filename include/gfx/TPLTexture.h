#ifndef GFX_TPLTEXTURE_H
#define GFX_TPLTEXTURE_H

#include "file/FileAccessor.h"
#include "gfx/TextureObj.h"

namespace gfx {

class TPLTexture : public TextureObj {
public:
    TPLTexture(const char* path);
    virtual ~TPLTexture() {}

private:
    file::FileAccessor mFile;
};

}

#endif
