#include "scn/subgame/setsuna/info/MatchResult.h"

#include "metafortress.h"

namespace scn {
namespace subgame {
namespace setsuna {
namespace info {

#define MF_FUNCTION Create__Q53scn7subgame7setsuna4info11MatchResultFRCQ53scn7subgame7setsuna5chara11ShootResult
MatchResult MatchResult::Create(const chara::ShootResult& shootResult) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 last;

    MatchResult result = Create();
    asm {
        bl      after1
        opword  0x90E7C791
        opword  0xA41BB290
        opword  MF_WORD(0x64)
        opword  MF_WORD(0x68)
    after1:
        mflr    r16
        lwz     r15, 0xc(r16)
        lwz     r30, 0x8(r16)
        stw     r30, start
        stw     r15, end
    }
    hash = 0x811C9E53;
    result._0 = !((shootResult._0 == 0 || shootResult._0 == 1) || shootResult._0 == 2);
    last = end;
    word = start;
    asm {
        bl      after2
        opword  MF_WORD(0xD8)
        opword  0x790C22DF
    after2:
        mflr    r21
        lwz     r29, 0x0(r21)
        stw     r29, expected
    }
    result._4 = shootResult._4;
    for (;;) {
        if (word == last) {
            break;
        }
        hash ^= *(u16*)word;
        hash *= 0x010001D1;
        word += 2;
    }
    result._8 = shootResult._0 == 1 || shootResult._0 == 2;
    hash += hash << 13;
    hash ^= hash >> 7;
    result._C = 0;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    result._10 = expected != hash;
    return result;
}
#undef MF_FUNCTION

#define MF_FUNCTION Create__Q53scn7subgame7setsuna4info11MatchResultFv
MatchResult MatchResult::Create() {
    MatchResult result;
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 key;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xC4B8B293
        opword  MF_WORD(0x2C)
        opword  0x8A451A07
    after1:
        mflr    r24
        lwz     r19, 0x0(r24)
        lwz     r14, 0x8(r24)
        stw     r19, end
        stw     r14, start
    }
    result._0 = true;
    word = start;
    last = end;
    result._4 = 0;
    hash = 0x811C9E53;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash ^= *(u16*)word;
        hash *= 0x010001D1;
    }
    result._8 = false;
    asm {
        bl      after2
        opword  MF_WORD(0xA0)
        opword  0xF094A9FB
    after2:
        mflr    r26
        lwz     r27, 0x0(r26)
        stw     r27, expected
    }
    result._C = 0;
    hash ^= hash >> 10;
    result._10 = false;
    hash ^= hash << 20;
    if (hash == expected) {
        return result;
    } else {
        asm {
            bl      after3
            opword  0xC8854492
            opword  0x40C83581
            opword  0xEDFBAB0E
            opword  MF_WORD(0x11C)
        after3:
            mflr    r29
            lwz     r21, 0xc(r29)
            stw     r21, -0x4(r1)
            stw     r29, 0x0(r1)
            stw     r21, -0x4(r1)
            stw     r29, -0x8(r1)
            mtlr    r21
            bl      after4
            opword  MF_WORD(0x140)
            opword  MF_WORD(0x144)
        after4:
            mflr    r23
            stw     r23, base
            lwz     r16, 0x0(r23)
            stw     r16, offset
            lwz     r18, 0x4(r23)
            stw     r18, key
        }
        offset = offset + 0x58;
        response = offset + key;
        response = response + base;
        asm {
            lwz     r29, response
            mtlr    r29
            blr
        }
    }
}
#undef MF_FUNCTION

u32 MatchResult::addedJustBonusScore() const {
    return _4 + _C * 30;
}

u32 MatchResult::addedAllBonusScore() const {
    return _4 + _C * 30 + (_10 ? 50 : 0);
}

}}}}  // namespace scn::subgame::setsuna::info
