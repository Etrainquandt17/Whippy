#include "mem/OperatorNewDelete.h"

#include "hel/common/ExplicitSingleton.h"
#include "hel/common/PointerWrapper.h"
#include "mem/HeapExp.h"
#include "mem/Memory.h"
#include "std/new.h"

using hel::common::ExplicitSingleton;
using hel::common::PointerWrapper;

namespace {

PointerWrapper<mem::IAllocator> t_allocator;
PointerWrapper<mem::IAllocator> t_globalNewDeleteAllocator;

mem::IAllocator& t_allocatorRef() {
    mem::Memory::SetupIfNotSetup();
    if (t_globalNewDeleteAllocator.wasSet()) {
        return t_globalNewDeleteAllocator.ref();
    } else if (t_allocator.wasSet()) {
        return t_allocator.ref();
    }
    return ExplicitSingleton<mem::Memory>::object_->mem1FixHeap();
}

void* t_operatorNew(u32 size) {
    return t_allocatorRef().allocatorAlloc(size, 4);
}

void* t_operatorNew(u32 size, mem::IAllocator& allocator) {
    return allocator.allocatorAlloc(size, 4);
}

void t_operatorDelete(void* ptr) {
    if (ptr != 0) {
        t_allocatorRef().allocatorFree(ptr);
    }
}

}

void* operator new(u32 size, mem::IAllocator& allocator) {
    return t_operatorNew(size, allocator);
}

void* operator new(u32 size, const std::nothrow_t&, mem::IAllocator& allocator) {
    return t_operatorNew(size, allocator);
}

void* operator new(u32 size) {
    return t_operatorNew(size);
}

void* operator new(u32 size, const std::nothrow_t&) {
    return t_operatorNew(size);
}

void* operator new[](u32 size) {
    return t_operatorNew(size);
}

void* operator new[](u32 size, const std::nothrow_t&) {
    return t_operatorNew(size);
}

void operator delete(void* ptr) {
    t_operatorDelete(ptr);
}

void operator delete(void* ptr, const std::nothrow_t&) {
    t_operatorDelete(ptr);
}

void operator delete[](void* ptr) {
    t_operatorDelete(ptr);
}

void operator delete[](void* ptr, const std::nothrow_t&) {
    t_operatorDelete(ptr);
}

namespace mem {
namespace OperatorNewDelete {

void SetDefaultAllocator(IAllocator& allocator) {
    t_allocator.set(allocator);
}

IAllocator& GetDefaultAllocator() {
    return t_allocator.ref();
}

void SetGlobalNewDeleteAllocator(IAllocator& allocator) {
    t_globalNewDeleteAllocator.set(allocator);
}

void UnsetGlobalNewDeleteAllocator(IAllocator&) {
    t_globalNewDeleteAllocator.reset();
}

}}  // namespace mem::OperatorNewDelete
