#include "gfx/GXFifoProtectCanceler.h"

#include "gfx/GXFifoMemoryManager.h"

namespace gfx {

GXFifoProtectCanceler::GXFifoProtectCanceler(GXFifoMemoryManager& manager)
    : mManager(&manager) {
    mManager->setWriteEnable();
}

GXFifoProtectCanceler::~GXFifoProtectCanceler() {
    mManager->setWriteDisable();
}

}  // namespace gfx
