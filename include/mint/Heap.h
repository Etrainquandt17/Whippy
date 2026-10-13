#ifndef MINT_HEAP_H
#define MINT_HEAP_H

#include "mem/AutoHeapExp.h"
#include "mem/ExplicitAutoDeleteArray.h"
#include "mem/HeapUnit.h"
#include "param/ParamAccessor.h"
#include "std/allocator.h"
#include "std/map.h"
#include "types.h"

namespace mintvm {

class MintSetting;

}

namespace mint {

class Heap {
public:
    explicit Heap(mintvm::MintSetting& setting);
    ~Heap();

    void* memAlloc(unsigned long size);
    void memFree(void* ptr);

private:
    typedef std::map<unsigned long, unsigned long, std::less<unsigned long>, std::allocator<std::pair<const unsigned long, unsigned long> > > Map;

    param::ParamAccessor mParam;
    // TODO: what the map holds; the destructor walks it and nothing else uses it.
    Map mMap;
    mintvm::MintSetting& mSetting;
    mem::AutoHeapExp mHeap;
    mem::ExplicitAutoDeleteArray<mem::HeapUnit, 32> mUnits;
};

}

#endif
