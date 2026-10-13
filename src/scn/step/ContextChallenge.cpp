#include "scn/step/ContextChallenge.h"

#include "metafortress.h"

namespace scn {
namespace step {

#define MF_FUNCTION Create__Q33scn4step16ContextChallengeFv
ContextChallenge ContextChallenge::Create() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 tail;
    u32 i;
    u32 limit;
    ContextChallenge context = {};

    asm {
        bl      after1
        opword  0xAC1B9D90
        opword  0x20073D80
        opword  MF_WORD(0x44)
        opword  0x2832D180
        opword  0xA8C9A592
        opword  MF_WORD(0x50)
    after1:
        mflr    r19
        lwz     r16, 0x14(r19)
        lwz     r30, 0x8(r19)
        stw     r30, end
        stw     r16, start
    }
    context._0 = 0;
    i = 1;
    tail = end;
    limit = tail - start + 1;
    hash = 0x811C9DC5;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(tail - 1 - i);
        hash *= 0x01000181;
    }
    context.mScore = challenge::Score();
    hash += hash << 13;
    hash ^= hash >> 7;
    asm {
        bl      after2
        opword  MF_WORD(0x19C)
        opword  0x776C0D16
    after2:
        mflr    r26
        lwz     r29, 0x0(r26)
        stw     r29, expected
    }
    context._88 = false;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    context._89 = expected != hash;
    return context;
}
#undef MF_FUNCTION

}}  // namespace scn::step
