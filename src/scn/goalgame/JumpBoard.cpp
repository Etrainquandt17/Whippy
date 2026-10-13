#include "scn/goalgame/JumpBoard.h"

#include "metafortress.h"

namespace scn {
namespace goalgame {

#define MF_FUNCTION effectJumpBoard__Q33scn8goalgame9JumpBoardFv
void JumpBoard::effectJumpBoard() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  0xA55BD40A
        opword  MF_WORD(0x28)
        opword  0x30528080
        opword  MF_WORD(0x30)
        opword  0xF006B509
    after1:
        mflr    r17
        lwz     r19, 0x4(r17)
        lwz     r25, 0xc(r17)
        stw     r19, start
        stw     r25, end
    }
    hash = 0;
    last = end;
    word = start;
    for (;;) {
        if (word == last) {
            break;
        }
        hash *= 151;
        hash += *(u16*)word;
        word += 2;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x78)
        opword  0x403EC7DA
    after2:
        mflr    r22
        lwz     r26, 0x0(r22)
        stw     r26, expected
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    _9F8 = expected == hash;
}
#undef MF_FUNCTION

}
}
