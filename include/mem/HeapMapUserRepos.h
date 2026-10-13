#ifndef MEM_HEAPMAPUSERREPOS_H
#define MEM_HEAPMAPUSERREPOS_H

#include "nrel/devkit/heapmap/IHeapMapUser.h"

namespace mem {

// TODO: the other functions.
class HeapMapUserRepos {
public:
    static void Register(nrel::devkit::heapmap::IHeapMapUser& user);
    static void Unregister(nrel::devkit::heapmap::IHeapMapUser& user);
};

}  // namespace mem

#endif
