#include "scn/subgame/common/boxmenu/SelectUnit.h"

#include "metafortress.h"

namespace scn {
namespace subgame {
namespace common {
namespace boxmenu {

bool SelectUnit::isSuspend() const {
    return mIsSuspend;
}

#define MF_FUNCTION suspendImpl__Q53scn7subgame6common7boxmenu10SelectUnitFv
void SelectUnit::suspendImpl() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 first;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  0x2D195B0A
        opword  0x07696F00
        opword  MF_WORD(0x2C)
        opword  MF_WORD(0x30)
        opword  0x00F04880
    after1:
        mflr    r19
        lwz     r22, 0x8(r19)
        lwz     r21, 0xc(r19)
        stw     r22, start
        add     r21, r22, r21
        stw     r21, end
    }
    hash = 0xB5;
    AbstractSuspendableTree::suspend();
    i = 1;
    first = start;
    limit = end - first + 1;
    for (; i != limit; i += 2) {
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(first + i - 1);
    }
    asm {
        bl      after2
        opword  MF_WORD(0x9C)
        opword  0x3235B289
    after2:
        mflr    r29
        lwz     r21, 0x0(r29)
        stw     r21, expected
    }
    mIsSuspend = expected == hash;
}
#undef MF_FUNCTION

void SelectUnit::resumeImpl() {
    mIsSuspend = false;
    AbstractSuspendableTree::resume();
}

}}}}  // namespace scn::subgame::common::boxmenu
