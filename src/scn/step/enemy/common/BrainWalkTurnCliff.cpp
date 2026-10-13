#include "scn/step/enemy/common/BrainWalkTurnCliff.h"

#include "metafortress.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateWalkStraight.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

BrainWalkTurnCliff::BrainWalkTurnCliff(Enemy& enemy) : BrainBase(enemy) {}

#define MF_FUNCTION onLanding__Q53scn4step5enemy6common18BrainWalkTurnCliffFv
bool BrainWalkTurnCliff::onLanding() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 subtrahend;
    volatile u32 anchor;
    volatile u32 offset;
    u32 hash;
    u32 i;
    u32 last;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x6EDFF10C
        opword  MF_WORD(0x2C)
        opword  0x4B181200
        opword  0xCCAC0281
    after1:
        mflr    r24
        lwz     r14, 0x0(r24)
        stw     r14, start
        lwz     r14, 0x8(r24)
        stw     r14, end
    }
    limit = end - start + 1;
    last = end;
    hash = 0x811C9E53;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001D1;
    }
    obj().stateChanger().setNextState<StateWalkStraight, Enemy*>(&obj());
    hash += hash << 3;
    asm {
        bl      after2
        opword  MF_WORD(0xF8)
        opword  0x22112E65
    after2:
        mflr    r24
        lwz     r22, 0x0(r24)
        stw     r22, expected
    }
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash == expected) {
        return true;
    }
    asm {
        stw     r19, -0x4(r1)
        bl      after3
        opword  MF_WORD(0x138)
        opword  0xC656A705
    after3:
        mflr    r19
        lwz     r27, 0x0(r19)
        stw     r27, 0x0(r1)
        stw     r19, 0x4(r1)
        mtlr    r27
        bl      after4
        opword  MF_WORD(0x158)
        opword  MF_WORD(0x15C)
    after4:
        mflr    r16
        lwz     r21, 0x4(r16)
        stw     r21, subtrahend
        lwz     r21, 0x0(r16)
        stw     r16, anchor
        stw     r21, offset
    }
    response = offset - subtrahend;
    response = response + anchor;
    asm {
        lwz     r17, response
        mtlr    r17
        blr
    }
}
#undef MF_FUNCTION

}}}}  // namespace scn::step::enemy::common
