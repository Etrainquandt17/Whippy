#include "scn/step/item/GetInfo.h"

#include "metafortress.h"

namespace scn {
namespace step {
namespace item {

GetInfo::GetInfo()
    : _0(15)
    , mSubKind(0) {
}

#define MF_FUNCTION subKind__Q43scn4step4item7GetInfoCFv
u32 GetInfo::subKind() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 hash;
    u32 limit;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0x0083DE15
    after1:
        mflr    r21
        lwz     r26, 0x0(r21)
        stw     r26, expected
        bl      after2
        opword  0x6D55D80A
        opword  MF_WORD(0x3C)
        opword  0x28FB8680
        opword  0xF89A3780
        opword  MF_WORD(0x48)
        opword  0xA151B202
    after2:
        mflr    r26
        lwz     r30, 0x10(r26)
        stw     r30, end
        lwz     r19, 0x4(r26)
        stw     r19, start
    }
    last = end;
    limit = last - start + 1;
    i = -1;
    last--;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash *= 151;
        hash += *(u16*)(last - i);
    }
    while (hash - expected != 0) {
    }
    return mSubKind;
}
#undef MF_FUNCTION

}}}  // namespace scn::step::item
