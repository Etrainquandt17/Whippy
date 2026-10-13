#ifndef GFX_GXFIFOPROTECTCANCELER_H
#define GFX_GXFIFOPROTECTCANCELER_H

#include "hel/common/PrivateSingleton.h"

namespace gfx {

class GXFifoMemoryManager;

class GXFifoProtectCanceler : private hel::common::PrivateSingleton<GXFifoProtectCanceler> {
public:
    GXFifoProtectCanceler(GXFifoMemoryManager& manager);
    ~GXFifoProtectCanceler();

private:
    GXFifoMemoryManager* mManager;
};

}  // namespace gfx

#endif
