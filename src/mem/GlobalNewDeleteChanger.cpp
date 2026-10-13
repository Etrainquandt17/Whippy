#include "mem/GlobalNewDeleteChanger.h"

#include "mem/OperatorNewDelete.h"

namespace mem {

GlobalNewDeleteChanger::GlobalNewDeleteChanger(IAllocator& allocator)
    : mAllocator(allocator) {
    OperatorNewDelete::SetGlobalNewDeleteAllocator(allocator);
}

GlobalNewDeleteChanger::~GlobalNewDeleteChanger() {
    OperatorNewDelete::UnsetGlobalNewDeleteAllocator(mAllocator);
}

}
