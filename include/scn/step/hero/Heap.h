#ifndef SCN_STEP_HERO_HEAP_H
#define SCN_STEP_HERO_HEAP_H

#include "mem/AutoHeapExp.h"
#include "mem/HeapExpArrayUser.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Heap {
public:
    Heap(mem::HeapExpArrayUser& user, u32 index);
    ~Heap();

    void setUseHeapGear();
    void flipGearAllocDir();
    mem::IAllocator& getAllocator();

private:
    mem::HeapExpArrayUser& mUser;
    mem::AutoHeapExp mHeapGear;
    bool mUseHeapGear;
    bool mIsGearAllocFromHead;
};

}}}  // namespace scn::step::hero

#endif
