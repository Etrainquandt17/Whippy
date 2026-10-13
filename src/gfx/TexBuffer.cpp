#include "gfx/TexBuffer.h"

#include "revolution/gx/GXTexture.h"
#include "revolution/os/OSCache.h"

namespace gfx {

TexBuffer::TexBuffer(mem::IAllocator& allocator, u16 width, u16 height, GXTexFmt format)
    : mDataBlock(GXGetTexBufferSize(width, height, format, false, 0), 0x20, allocator)
    , mWidth(width & 0xFFFF)
    , mHeight(height & 0xFFFF)
    , mFormat(format) {
    DCInvalidateRange(block().startAddress(), block().size());
}

TexBuffer::~TexBuffer() {}

mem::MemBlock TexBuffer::block() const {
    return mDataBlock.block();
}

u16 TexBuffer::width() const {
    return mWidth;
}

u16 TexBuffer::height() const {
    return mHeight;
}

GXTexFmt TexBuffer::format() const {
    return mFormat;
}

}
