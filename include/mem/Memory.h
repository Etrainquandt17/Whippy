#ifndef MEM_MEMORY_H
#define MEM_MEMORY_H

namespace mem {

class HeapCompaction;
class HeapExp;
class IAllocator;

class Memory {
public:
    static void SetupIfNotSetup();

    HeapCompaction& externalHeap();
    IAllocator& sceneHeap();
    HeapExp& mem1FixHeap();
    HeapExp& mem2FixHeap();
};

}  // namespace mem

#endif
