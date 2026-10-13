#include "scn/step/info/InfoGameStatus.h"

#include "metafortress.h"

namespace scn {
namespace step {
namespace info {

void InfoGameStatus::startAnimOut() {
    mLayout.setAnimByName("Out");
    mLayout.start(false);
    _2760 = false;
}

#define MF_FUNCTION startAnimOutS__Q43scn4step4info14InfoGameStatusFv
void InfoGameStatus::startAnimOutS() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 p;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0xFEBB0852
    after1:
        mflr    r18
        lwz     r22, 0x0(r18)
        stw     r22, expected
        bl      after2
        opword  MF_WORD(0x34)
        opword  MF_WORD(0x38)
        opword  0x74479F93
        opword  0xBC95BE0A
    after2:
        mflr    r18
        lwz     r21, 0x0(r18)
        lwz     r29, 0x4(r18)
        stw     r21, start
        stw     r29, end
    }
    mLayout.setAnimByName("OutS");
    last = end;
    p = start;
    hash = 0x811C9E07;
    p -= 2;
    while (p != last - 2) {
        p += 2;
        hash ^= *(u16*)p;
        hash *= 0x010001A7;
    }
    hash += hash << 13;
    mLayout.start(false);
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    _2760 = expected != hash;
}
#undef MF_FUNCTION

#define MF_FUNCTION startAnimInS__Q43scn4step4info14InfoGameStatusFv
void InfoGameStatus::startAnimInS() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0x54D63381
        opword  0xB85FC690
        opword  MF_WORD(0x28)
    after1:
        mflr    r14
        lwz     r27, 0xc(r14)
        stw     r27, start
        lwz     r25, 0x0(r14)
        stw     r25, end
    }
    hash = 0x811C9E07;
    mLayout.setAnimByName("InS");
    limit = end - start + 1;
    i = 1;
    last = end - 1;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(last - i);
        hash *= 0x010001A7;
    }
    mLayout.start(false);
    asm {
        bl      after2
        opword  MF_WORD(0xA8)
        opword  0x0EBB3821
    after2:
        mflr    r15
        lwz     r25, 0x0(r15)
        stw     r25, expected
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    _2760 = expected == hash;
}
#undef MF_FUNCTION

#define MF_FUNCTION bossPanel__Q43scn4step4info14InfoGameStatusFv
BossPanel* InfoGameStatus::bossPanel() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash = 0;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0xAC79C791
    after1:
        mflr    r30
        lwz     r23, 0x0(r30)
        stw     r23, end
        bl      after2
        opword  MF_WORD(0x38)
        opword  0x44A43A81
    after2:
        mflr    r30
        lwz     r23, 0x0(r30)
        stw     r23, start
    }
    base = start;
    limit = end - base + 1;
    asm {
        bl      after3
        opword  MF_WORD(0x60)
        opword  0x9E3F8D74
    after3:
        mflr    r25
        lwz     r14, 0x0(r25)
        stw     r14, expected
    }
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash *= 37;
        hash += *(u16*)(base + i - 1);
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    while (hash - expected != 0) {
    }
    return _194;
}
#undef MF_FUNCTION

}}}  // namespace scn::step::info
