#include "info/common/AddWiiRemote.h"

#include "metafortress.h"

namespace info {
namespace common {

#define MF_FUNCTION phaseOn__Q44info6common12AddWiiRemote6RemoteFv
void AddWiiRemote::Remote::phaseOn() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    register u32 hash;
    register u32 word;

    asm {
        bl      after1
        opword  0xC2F67108
        opword  MF_WORD(0x28)
        opword  0x206FFA93
        opword  0x88426704
        opword  MF_WORD(0x34)
    after1:
        mflr    r20
        lwz     r26, 0x4(r20)
        lwz     r24, 0x10(r20)
        stw     r26, end
        stw     r24, start
        lwz     r28, end
        lwz     word, start
        li      hash, 0
        subi    word, word, 2
        subi    r29, r28, 2
        b       test
    next:
        addi    word, word, 2
        mulli   hash, hash, 193
        lhz     r28, 0x0(word)
        add     hash, hash, r28
    test:
        cmplw   cr4, word, r29
        bne     cr4, next
        bl      after2
        opword  MF_WORD(0x80)
        opword  0xA2D436AF
    after2:
        mflr    r26
        lwz     r16, 0x0(r26)
        stw     r16, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected != 0 || !isConnected()) {
        const char* name = "ToOff";
        _90.play(name);
        _540.play(name);
        _220.rootPane().show();
        _3B0.rootPane().show();
        mPhase = 3;
    }
}
#undef MF_FUNCTION

}
}
