#ifndef NREL_DEVKIT_HEAPMAP_IHEAPMAPUSER_H
#define NREL_DEVKIT_HEAPMAP_IHEAPMAPUSER_H

namespace nrel {
namespace devkit {
namespace heapmap {

// TODO: nine more virtual functions follow the destructor (heapName,
// fragmentBlockCount, usedBlockCount, totalHeapSize, usedHeapSize,
// startAddress, endAddress, drawUsedBlocks, drawFragmentBlocks).
class IHeapMapUser {
public:
    virtual ~IHeapMapUser();
};

}}}  // namespace nrel::devkit::heapmap

#endif
