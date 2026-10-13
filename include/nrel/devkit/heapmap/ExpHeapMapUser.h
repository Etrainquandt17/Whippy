#ifndef NREL_DEVKIT_HEAPMAP_EXPHEAPMAPUSER_H
#define NREL_DEVKIT_HEAPMAP_EXPHEAPMAPUSER_H

#include "nrel/devkit/heapmap/IHeapMapUser.h"
#include "revolution/mem.h"

namespace nrel {
namespace devkit {
namespace heapmap {

// TODO: the virtual functions IHeapMapUser does not declare yet.
class ExpHeapMapUser : public IHeapMapUser {
public:
    ExpHeapMapUser(MEMiHeapHead* heap, const char* name);
    virtual ~ExpHeapMapUser();

private:
    MEMiHeapHead* mHeap;
    const char* mName;
};

}}}  // namespace nrel::devkit::heapmap

#endif
