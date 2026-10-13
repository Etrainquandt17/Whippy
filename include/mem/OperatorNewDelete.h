#ifndef MEM_OPERATORNEWDELETE_H
#define MEM_OPERATORNEWDELETE_H

#include "mem/IAllocator.h"
#include "types.h"

namespace mem {

namespace OperatorNewDelete {

void SetDefaultAllocator(IAllocator& allocator);
void SetGlobalNewDeleteAllocator(IAllocator& allocator);
void UnsetGlobalNewDeleteAllocator(IAllocator& allocator);

}

}  // namespace mem

#endif
