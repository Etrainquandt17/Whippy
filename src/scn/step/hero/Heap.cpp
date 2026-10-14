#include "scn/step/hero/Heap.h"

#include "hel/common/FixedStringIN.h"
#include "metafortress.h"

using hel::common::FixedStringIN;

namespace scn {
namespace step {
namespace hero {

Heap::Heap(mem::HeapExpArrayUser& user, u32 index)
    : mUser(user)
    , mHeapGear(mUser.obj(), 0x20800, FixedStringIN<char, 32>::FromFormat("HeroGear%02lu", index))
    , mUseHeapGear(false)
    , mIsGearAllocFromHead(true) {
}

Heap::~Heap() {
}

#define MF_FUNCTION setUseHeapGear__Q43scn4step4hero4HeapFv
void Heap::setUseHeapGear() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 size;
    u32 hash;
    u32 i;
    u32 base;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
    after1:
        mflr    r21
        lwz     r27, 0x0(r21)
        lwz     r28, 0x4(r21)
        stw     r28, start
        stw     r27, end
    }
    base = start;
    size = end - base;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash *= 37;
        hash += *(u16*)(base + i - 1);
    }
    asm {
        bl      after2
        opword  MF_WORD(0x7C)
        opword  0x36FF3836
    after2:
        mflr    r29
        lwz     r30, 0x0(r29)
        stw     r30, expected
    }
    mUseHeapGear = expected == hash;
}
#undef MF_FUNCTION

void Heap::flipGearAllocDir() {
    mIsGearAllocFromHead = !mIsGearAllocFromHead;
}

mem::IAllocator& Heap::getAllocator() {
    if (mUseHeapGear) {
        if (mIsGearAllocFromHead) {
            return mHeapGear.obj().allocFromHeadAllocator();
        } else {
            return mHeapGear.obj().allocFromTailAllocator();
        }
    }
    return mUser.obj();
}

}}}  // namespace scn::step::hero
