#ifndef GFX_TEXBUFFER_H
#define GFX_TEXBUFFER_H

#include "mem/DataBlock.h"
#include "revolution/gx/GXEnum.h"
#include "types.h"

namespace gfx {

class TexBuffer {
public:
    TexBuffer(mem::IAllocator& allocator, u16 width, u16 height, GXTexFmt format);
    ~TexBuffer();

    mem::MemBlock block() const;
    u16 width() const;
    u16 height() const;
    GXTexFmt format() const;

private:
    mem::DataBlock mDataBlock;
    u16 mWidth;
    u16 mHeight;
    GXTexFmt mFormat;
};

}

#endif
