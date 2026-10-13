#ifndef GFX_GXFIFOMEMORYMANAGER_H
#define GFX_GXFIFOMEMORYMANAGER_H

#include "hel/common/PrivateSingleton.h"
#include "types.h"

namespace gfx {

class GXFifoMemoryManager : private hel::common::PrivateSingleton<GXFifoMemoryManager> {
public:
    GXFifoMemoryManager(u32 size, u32 arg);
    ~GXFifoMemoryManager();

    void* data();
    void setWriteEnable();
    void setWriteDisable();
    bool isWriteEnable() const;

private:
    u32 mSize;
    u32 _4;
    void* mData;
    bool mIsWriteEnable;
};

}

#endif
