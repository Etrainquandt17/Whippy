#include <kdc/revolution/MEM.h>
#include <kdc/revolution/OS.h>

#define MEM_UNT_HEAP_MAGIC FOURCC('U', 'N', 'T', 'H')

typedef struct MEMiUntMBlock {
    struct MEMiUntMBlock* next; // at 0x0
} MEMiUntMBlock;

typedef struct MEMiUntHeapHead {
    MEMiUntMBlock* freeList; // at 0x0
    u32 unitSize;            // at 0x4
} MEMiUntHeapHead;

// ROUND_UP and ROUND_UP_PTR give other instructions here: the first masks with the negated
// alignment, the second does not group the alignment minus one.
#define MEM_ROUND_UP(x, align) (((x) + ((align) - 1)) & ~((align) - 1))

// Size of base and unit heap head
#define MEM_UNT_HEAP_HEAD_SIZE (sizeof(MEMiHeapHead) + sizeof(MEMiUntHeapHead))

static MEMiUntHeapHead*
GetUntHeapHeadPtrFromHeapHead_(const MEMiHeapHead* heap) {
    return AddU32ToPtr(heap, sizeof(MEMiHeapHead));
}

MEMiHeapHead* MEMCreateUnitHeapEx(void* start, u32 size, u32 unitSize,
                                  s32 align, u16 opt) {
    MEMiHeapHead* heap;
    MEMiUntHeapHead* unt;
    void* end;
    void* blocks;
    u32 count;

    heap = ROUND_UP_PTR(start, 4);
    end = ROUND_DOWN_PTR(AddU32ToPtr(start, size), 4);

    if (ComparePtr(heap, end) > 0) {
        return NULL;
    }

    unt = GetUntHeapHeadPtrFromHeapHead_(heap);

    unitSize = MEM_ROUND_UP(unitSize, align);
    blocks = (void*)MEM_ROUND_UP(
        GetUIntPtr(AddU32ToPtr(unt, sizeof(MEMiUntHeapHead))), align);

    if (ComparePtr(blocks, end) > 0) {
        return NULL;
    }

    count = GetOffsetFromPtr(blocks, end) / unitSize;
    if (count == 0) {
        return NULL;
    }

    MEMiInitHeapHead(heap, MEM_UNT_HEAP_MAGIC, blocks,
                     AddU32ToPtr(blocks, count * unitSize), opt);

    unt->freeList = blocks;
    unt->unitSize = unitSize;

    {
        MEMiUntMBlock* block = unt->freeList;
        u32 i;

        for (i = 0; i < count - 1; i++, block = block->next) {
            block->next = AddU32ToPtr(block, unitSize);
        }

        block->next = NULL;
    }

    return heap;
}

void* MEMAllocFromUnitHeap(MEMiHeapHead* heap) {
    MEMiUntHeapHead* unt = GetUntHeapHeadPtrFromHeapHead_(heap);
    MEMiUntMBlock* block;

    LockHeap(heap);

    block = unt->freeList;
    if (block != NULL) {
        unt->freeList = block->next;
    }

    UnlockHeap(heap);

    if (block != NULL) {
        FillAllocMemory(heap, block, unt->unitSize);
    }

    return block;
}

void MEMFreeToUnitHeap(MEMiHeapHead* heap, void* memBlock) {
    if (memBlock == NULL) {
        return;
    }

    {
        MEMiUntHeapHead* unt = GetUntHeapHeadPtrFromHeapHead_(heap);

        LockHeap(heap);

        ((MEMiUntMBlock*)memBlock)->next = unt->freeList;
        unt->freeList = memBlock;

        UnlockHeap(heap);
    }
}

u32 MEMCalcHeapSizeForUnitHeap(u32 unitSize, u32 count, s32 align) {
    return MEM_UNT_HEAP_HEAD_SIZE + (align - 4) +
           count * MEM_ROUND_UP(unitSize, align);
}
