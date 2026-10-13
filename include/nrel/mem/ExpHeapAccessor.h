#ifndef NREL_MEM_EXPHEAPACCESSOR_H
#define NREL_MEM_EXPHEAPACCESSOR_H

#include "revolution/mem.h"

namespace nrel {
namespace mem {

// TODO: the other functions, and the other dump styles.
class ExpHeapAccessor {
public:
    enum DumpStyle {
        DUMP_STYLE_0,
    };

    ExpHeapAccessor(MEMiHeapHead* heap);
    ~ExpHeapAccessor();

    void dump(DumpStyle style) const;

private:
    MEMiHeapHead* mHeap;
};

}}  // namespace nrel::mem

#endif
