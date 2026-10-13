#include "scn/arena/select/ChoseData.h"

#include "metafortress.h"

using scn::step::hero::KIND_NONE;
using scn::step::hero::Kind;

namespace scn {
namespace arena {
namespace select {

#define MF_FUNCTION initKind__Q53scn5arena6select9ChoseData10PlayerDataFQ43scn4step4hero4Kind
void ChoseData::PlayerData::initKind(Kind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 value;
    u32 word;
    bool zero;
    u32 last;

    value = 0x811D0000;
    hash = value - 0x61F9;
    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0x0F17A828
    after1:
        mflr    r17
        lwz     r23, 0x0(r17)
        stw     r23, expected
    }
    zero = false;
    mIsEntry = zero;
    asm {
        bl      after2
        opword  0xB0F96581
        opword  0xE4A29B0C
        opword  MF_WORD(0x58)
        opword  0x4F0BE807
        opword  MF_WORD(0x60)
    after2:
        mflr    r21
        lwz     r27, 0x8(r21)
        stw     r27, start
        lwz     r15, 0x10(r21)
        add     r27, r27, r15
        stw     r27, end
    }
    word = start;
    last = end;
    zero = false;
    mIsNG = zero;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        value = *(u16*)word;
        hash ^= value;
        hash *= 0x010001A7;
    }
    hash += hash << 3;
    mDecide = KIND_NONE;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash -= expected;
    if (hash != 0) {
        volatile u32 offset;
        volatile u32 addend;
        volatile u32 base2;
        volatile u32 response;

        asm {
            bl      after3
            opword  MF_WORD(0xEC)
        after3:
            mflr    r27
            lwz     r15, 0x0(r27)
            stw     r15, -0x4(r1)
            stw     r27, 0x0(r1)
            stw     r15, -0x4(r1)
            stw     r27, -0x8(r1)
            mtlr    r15
            bl      after4
            opword  MF_WORD(0x110)
            opword  0xF8F3A393
            opword  MF_WORD(0x118)
        after4:
            mflr    r14
            lwz     r22, 0x8(r14)
            stw     r22, addend
            lwz     r22, 0x0(r14)
            stw     r14, base2
            stw     r22, offset
        }
        offset = offset + 0x22;
        addend = 0;
        response = offset;
        response = response + base2;
        asm {
            lwz     r17, response
            mtlr    r17
            blr
        }
    } else {
        mSelect = kind;
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION initPlayer__Q53scn5arena6select9ChoseData10PlayerDataFUl
void ChoseData::PlayerData::initPlayer(u32 player) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    hash = 0x811C9E29;
    asm {
        bl      after1
        opword  0xEF5FD00B
        opword  0xB8C10C81
        opword  MF_WORD(0x38)
        opword  0x6C5BB080
        opword  MF_WORD(0x40)
        opword  0x08EE6C91
    after1:
        mflr    r30
        lwz     r27, 0x10(r30)
        stw     r27, end
        lwz     r25, 0x8(r30)
        stw     r25, start
    }
    i = 1;
    last = end;
    limit = last - start + 1;
    asm {
        bl      after2
        opword  MF_WORD(0x74)
        opword  0xE6D5CBBB
    after2:
        mflr    r22
        lwz     r27, 0x0(r22)
        stw     r27, expected
    }
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001AB;
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected == 0) {
        const Kind kinds[] = {
            step::hero::KIND_KIRBY_0,
            step::hero::KIND_KIRBY_1,
            step::hero::KIND_KIRBY_2,
            step::hero::KIND_KIRBY_3,
        };
        initKind(kinds[player]);
    } else {
        volatile u32 response;
        volatile u32 base2;
        volatile u32 offset;
        volatile u32 addend;

        asm {
            bl      after3
            opword  0x36794C03
            opword  MF_WORD(0x11C)
        after3:
            mflr    r28
            lwz     r20, 0x4(r28)
            stw     r20, -0x4(r1)
            stw     r28, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r28, -0x8(r1)
            mtlr    r20
            bl      after4
            opword  MF_WORD(0x140)
            opword  0x86396905
            opword  0x20731080
            opword  MF_WORD(0x14C)
        after4:
            mflr    r23
            lwz     r21, 0x0(r23)
            lwz     r14, 0xc(r23)
            stw     r14, addend
            stw     r21, offset
            stw     r23, base2
        }
        offset = offset + 0x2F;
        response = offset ^ addend;
        response = response + base2;
        asm {
            lwz     r28, response
            mtlr    r28
            blr
        }
    }
}
#undef MF_FUNCTION

// The link dropped this one.
void ChoseData::PlayerData::init() {
    initPlayer(0);
}

#define MF_FUNCTION init__Q43scn5arena6select9ChoseDataFv
void ChoseData::init() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xC71BAB91
    after1:
        mflr    r18
        lwz     r20, 0x0(r18)
        stw     r20, expected
        bl      after2
        opword  0x0423F990
        opword  MF_WORD(0x40)
        opword  MF_WORD(0x44)
        opword  0xE4533380
        opword  0x74AF1101
    after2:
        mflr    r20
        lwz     r28, 0x4(r20)
        lwz     r23, 0x8(r20)
        stw     r28, end
        stw     r23, start
    }
    mEntryNum = 0;
    hash = 0xBF;
    i = 1;
    last = end;
    limit = last - start + 1;
    _4 = 0;
    while (i != limit) {
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(last - 1 - i);
        i += 2;
    }
    hash ^= expected;
    if (hash != 0) {
        volatile u32 base2;
        volatile u32 response;
        volatile u32 addend;
        volatile u32 offset;

        asm {
            bl      after3
            opword  MF_WORD(0xC8)
        after3:
            mflr    r29
            lwz     r20, 0x0(r29)
            stw     r20, -0x4(r1)
            stw     r29, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r29, -0x8(r1)
            mtlr    r20
            bl      after4
            opword  MF_WORD(0xEC)
            opword  0x38878A91
            opword  MF_WORD(0xF4)
        after4:
            mflr    r24
            stw     r24, base2
            lwz     r26, 0x0(r24)
            stw     r26, offset
            lwz     r21, 0x8(r24)
            stw     r21, addend
        }
        offset = offset - 0x25;
        response = offset + addend;
        response = response + base2;
        asm {
            lwz     r16, response
            mtlr    r16
            blr
        }
    } else {
        for (int n = 0; n < 4; n++) {
            mPlayers[n].initPlayer(n);
            checkData();
        }
    }
}
#undef MF_FUNCTION

void ChoseData::init(u32 player) {
    mPlayers[player].initPlayer(player);
    checkData();
}

#define MF_FUNCTION setArenaDataPlayer__Q43scn5arena6select9ChoseDataFRCQ33scn5arena9ArenaData
void ChoseData::setArenaDataPlayer(const ArenaData& data) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 value;
    u32 i;
    u32 base;
    u32 limit;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  MF_WORD(0x30)
        opword  0xB146FD05
        opword  0x80ABA493
    after1:
        mflr    r27
        lwz     r26, 0x0(r27)
        lwz     r29, 0x4(r27)
        add     r26, r26, r27
        add     r29, r29, r26
        stw     r26, start
        stw     r29, end
    }
    i = 1;
    base = start;
    limit = end - base + 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash += *(u16*)(base + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
        i += 2;
    }
    init();
    asm {
        bl      after2
        opword  MF_WORD(0xA4)
        opword  0xDFEA41B6
    after2:
        mflr    r24
        lwz     r17, 0x0(r24)
        stw     r17, expected
    }
    value = hash << 13;
    hash += value;
    value = hash >> 7;
    hash ^= value;
    value = hash << 3;
    hash += value;
    value = hash >> 17;
    hash ^= value;
    value = hash << 5;
    hash += value;
    value = expected;
    value = hash - value;
    if (value == 0) {
        const ArenaDataPlayer& from = reinterpret_cast<const ArenaDataPlayer&>(data);
        for (u32 n = 0; n < 4; n++) {
            if (from.mEntries[n].mIsEntry && from.mEntries[n].mKind != KIND_NONE) {
                switch (from.mEntries[n].mKind) {
                case step::hero::KIND_KIRBY_0:
                case step::hero::KIND_KIRBY_1:
                case step::hero::KIND_KIRBY_2:
                case step::hero::KIND_KIRBY_3:
                case step::hero::KIND_META:
                case step::hero::KIND_DEDEDE:
                case step::hero::KIND_DEE:
                    mPlayers[n].initKind(from.mEntries[n].mKind);
                    mPlayers[n].mIsEntry = true;
                    decide(n);
                    checkData();
                    break;
                }
            }
        }
    } else {
        volatile u32 response;
        volatile u32 base2;
        volatile u32 offset;
        volatile u32 addend;

        asm {
            bl      after3
            opword  MF_WORD(0x168)
            opword  0x4CF63A93
            opword  0x48BA7D81
        after3:
            mflr    r14
            addi    r23, r14, 0x18
            mtlr    r23
            lwz     r30, 0x0(r14)
            stw     r30, -0x4(r1)
            stw     r23, 0x0(r1)
            stw     r14, 0x4(r1)
            blrl
            bl      after4
            opword  MF_WORD(0x198)
            opword  0x344FFE80
            opword  MF_WORD(0x1A0)
        after4:
            mflr    r27
            lwz     r20, 0x8(r27)
            stw     r20, addend
            lwz     r20, 0x0(r27)
            stw     r27, base2
            stw     r20, offset
        }
        offset = offset + 0xC5;
        addend = 0;
        response = offset;
        response = response + base2;
        asm {
            lwz     r16, response
            mtlr    r16
            blr
        }
    }
}
#undef MF_FUNCTION

ChoseData::ArenaDataPlayer ChoseData::getArenaDataPlayer() {
    ArenaDataPlayer result;
    result.mNum = 0;
    for (u32 i = 0; i < 4; i++) {
        if (isDecide(i)) {
            result.mNum++;
            result.mEntries[i].mIsEntry = true;
            result.mEntries[i].mKind = getDecide(i);
            switch (result.mEntries[i].mKind) {
            case step::hero::KIND_KIRBY_0:
            case step::hero::KIND_KIRBY_1:
            case step::hero::KIND_KIRBY_2:
            case step::hero::KIND_KIRBY_3:
                result.mEntries[i].mAbility = static_cast<step::hero::AbilityKind>(0);
                break;
            case step::hero::KIND_META:
                result.mEntries[i].mAbility = step::hero::ABILITY_KIND_META;
                break;
            case step::hero::KIND_DEDEDE:
                result.mEntries[i].mAbility = step::hero::ABILITY_KIND_DEDEDE;
                break;
            case step::hero::KIND_DEE:
                result.mEntries[i].mAbility = step::hero::ABILITY_KIND_DEE;
                break;
            default:
                result.mEntries[i].mIsEntry = false;
                result.mEntries[i].mKind = static_cast<Kind>(i);
                result.mEntries[i].mAbility = static_cast<step::hero::AbilityKind>(0);
                break;
            }
        } else {
            result.mEntries[i].mIsEntry = false;
            result.mEntries[i].mKind = static_cast<Kind>(i);
            result.mEntries[i].mAbility = static_cast<step::hero::AbilityKind>(0);
        }
    }
    return result;
}

u32 ChoseData::entryNum() {
    mEntryNum = 0;
    for (int i = 0; i < 4; i++) {
        if (isEntry(i)) {
            mEntryNum++;
        }
    }
    return mEntryNum;
}

// The link dropped this one.
u32 ChoseData::entryBit() {
    u32 bits = 0;
    for (int i = 0; i < 4; i++) {
        if (isEntry(i)) {
            bits |= 1 << i;
        }
    }
    return bits;
}

void ChoseData::entry(u32 player) {
    PlayerData& data = mPlayers[player];
    data.initPlayer(player);
    data.mIsEntry = true;
    checkData();
}

bool ChoseData::isEntry(u32 player) {
    return mPlayers[player].mIsEntry == true;
}

Kind ChoseData::getSelect(u32 player) {
    if (isEntry(player)) {
        return mPlayers[player].mSelect;
    }
    return KIND_NONE;
}

void ChoseData::prev(u32 player) {
    if (isEntry(player) && !isDecide(player)) {
        Kind kind;
        u32 idx = getSelectIdx(player);
        do {
            if (idx > getKindToIdx(step::hero::KIND_KIRBY_0)) {
                idx--;
            } else {
                switch (player) {
                case 0:
                    idx = getKindToIdx(step::hero::KIND_DEE);
                    break;
                case 1:
                case 2:
                case 3:
                    idx = getKindToIdx(KIND_NONE);
                    break;
                }
            }
            kind = getIdxToKind(player, idx);
        } while (chkAllKind(player, kind));
        mPlayers[player].mSelect = kind;
        checkData();
    }
}

void ChoseData::next(u32 player) {
    if (isEntry(player) && !isDecide(player)) {
        Kind kind;
        u32 idx = getSelectIdx(player);
        do {
            switch (player) {
            case 0:
                if (idx < getKindToIdx(step::hero::KIND_DEE)) {
                    idx++;
                } else {
                    idx = getKindToIdx(step::hero::KIND_KIRBY_0);
                }
                break;
            case 1:
            case 2:
            case 3:
                idx = idx < getKindToIdx(KIND_NONE) ? idx + 1 : getKindToIdx(step::hero::KIND_KIRBY_0);
                break;
            }
            kind = getIdxToKind(player, idx);
        } while (chkAllKind(player, kind));
        mPlayers[player].mSelect = kind;
        checkData();
    }
}

void ChoseData::decide(u32 player) {
    if (isEntry(player) && !isDecide(player) && !isNG(player)) {
        mPlayers[player].mDecide = getSelect(player);
        checkData();
    }
}

#define MF_FUNCTION cancel__Q43scn5arena6select9ChoseDataFUl
void ChoseData::cancel(u32 player) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 hash;
    u32 base;
    u32 size;

    hash = 0x811C9E53;
    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0x18E16492
        opword  MF_WORD(0x38)
        opword  0xE2330A0C
    after1:
        mflr    r19
        lwz     r21, 0x0(r19)
        add     r21, r21, r19
        lwz     r20, 0x8(r19)
        stw     r21, start
        add     r20, r20, r21
        stw     r20, end
    }
    size = end - start;
    base = start;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001D1;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xA0)
        opword  0xEC8031A6
    after2:
        mflr    r19
        lwz     r22, 0x0(r19)
        stw     r22, expected
    }
    if (hash - expected != 0 || isEntry(player)) {
        mPlayers[player].mDecide = KIND_NONE;
        checkData();
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION getDecide__Q43scn5arena6select9ChoseDataFUl
Kind ChoseData::getDecide(u32 player) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 t;
    u32 value;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
        opword  0xBCE1A580
    after1:
        mflr    r18
        lwz     r20, 0x0(r18)
        lwz     r22, 0x4(r18)
        add     r20, r20, r18
        add     r22, r22, r20
        stw     r20, start
        stw     r22, end
    }
    value = 0x811D0000;
    hash = value - 0x61AD;
    asm {
        bl      after2
        opword  MF_WORD(0x5C)
        opword  0x5C2A4A2A
    after2:
        mflr    r24
        lwz     r18, 0x0(r24)
        stw     r18, expected
    }
    t = start;
    value = end;
    value = value - t;
    limit = value + 1;
    i = 1;
    base = start;
    t = 0x010001D1;
    while (i != limit) {
        value = base + i;
        value = *(u16*)(value - 1);
        hash ^= value;
        hash *= t;
        i += 2;
    }
    limit = hash >> 10;
    hash ^= limit;
    limit = hash << 20;
    hash ^= limit;
    limit = expected;
    hash = hash - limit;
    if (hash != 0) {
        if (isEntry(player) && isDecide(player)) {
            return mPlayers[player].mDecide;
        }
        return KIND_NONE;
    }
    volatile u32 base2;
    volatile u32 addend;
    volatile u32 response;
    volatile u32 offset;

    asm {
        bl      after3
        opword  0xAB4ADA02
        opword  0x1C202880
        opword  MF_WORD(0x11C)
    after3:
        mflr    r21
        lwz     r16, 0x8(r21)
        stw     r16, -0x4(r1)
        stw     r21, 0x0(r1)
        stw     r16, -0x4(r1)
        stw     r21, -0x8(r1)
        mtlr    r16
        bl      after4
        opword  MF_WORD(0x140)
        opword  0x7226D90A
        opword  MF_WORD(0x148)
    after4:
        mflr    r22
        lwz     r30, 0x0(r22)
        lwz     r26, 0x8(r22)
        stw     r26, addend
        stw     r30, offset
        stw     r22, base2
    }
    response = offset - addend;
    response = response + base2;
    asm {
        lwz     r25, response
        mtlr    r25
        blr
    }
}
#undef MF_FUNCTION

bool ChoseData::isDecide(u32 player) {
    if (isEntry(player)) {
        return mPlayers[player].mDecide != KIND_NONE;
    }
    return false;
}

bool ChoseData::isAllDecide() {
    u32 num = entryNum();
    u32 count = 0;
    for (int i = 0; i < 4; i++) {
        if (isDecide(i)) {
            count++;
        }
    }
    return num == count;
}

bool ChoseData::isNG(u32 player) {
    if (isEntry(player)) {
        return mPlayers[player].mIsNG;
    }
    return false;
}

bool ChoseData::isRetire(u32 player) {
    if (isEntry(player) && !isDecide(player)) {
        return mPlayers[player].mSelect == KIND_NONE;
    }
    return false;
}

#define MF_FUNCTION checkData__Q43scn5arena6select9ChoseDataFv
void ChoseData::checkData() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 hash;
    u32 value;
    u32 base;
    u32 limit;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x983A2AAB
    after1:
        mflr    r16
        lwz     r15, 0x0(r16)
        stw     r15, expected
    }
    for (int n = 0; n < 4; n++) {
        mPlayers[n].mIsNG = false;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x60)
        opword  0x848E0180
        opword  MF_WORD(0x68)
        opword  0xB4928592
    after2:
        mflr    r23
        lwz     r25, 0x0(r23)
        add     r25, r25, r23
        stw     r25, start
        lwz     r15, 0x8(r23)
        add     r25, r25, r15
        stw     r25, end
    }
    i = 1;
    base = start;
    value = end;
    value = value - base;
    limit = value + 1;
    while (i != limit) {
        hash = hash * 37;
        value = base + i;
        value = *(u16*)(value - 1);
        hash = hash + value;
        i += 2;
    }
    value = expected;
    value = hash ^ value;
    if (value == 0) {
        for (int a = 0; a < 4; a++) {
            if (isEntry(a) && isDecide(a)) {
                for (int b = 0; b < 4; b++) {
                    if (a != b && isEntry(b) && !isDecide(b)) {
                        if (getSelect(b) != KIND_NONE) {
                            if (getDecide(a) == getSelect(b)) {
                                mPlayers[b].mIsNG = true;
                            }
                        } else {
                            mPlayers[b].mIsNG = true;
                        }
                    }
                }
            }
        }
    } else {
        volatile u32 offset;
        volatile u32 response;
        volatile u32 addend;
        volatile u32 base2;

        asm {
            bl      after3
            opword  0x5F918503
            opword  MF_WORD(0x1AC)
        after3:
            mflr    r25
            lwz     r21, 0x4(r25)
            stw     r21, -0x4(r1)
            stw     r25, 0x0(r1)
            stw     r21, -0x4(r1)
            stw     r25, -0x8(r1)
            mtlr    r21
            bl      after4
            opword  MF_WORD(0x1D0)
            opword  0x24A51180
            opword  0x44815680
            opword  MF_WORD(0x1DC)
        after4:
            mflr    r21
            lwz     r27, 0x0(r21)
            stw     r21, base2
            lwz     r19, 0xc(r21)
            stw     r27, offset
            stw     r19, addend
        }
        offset = offset - 0x3D;
        response = offset ^ addend;
        response = response + base2;
        asm {
            lwz     r25, response
            mtlr    r25
            blr
        }
    }
}
#undef MF_FUNCTION

u32 ChoseData::getSelectIdx(u32 player) {
    return getKindToIdx(mPlayers[player].mSelect);
}

u32 ChoseData::getKindToIdx(Kind kind) {
    const u32 idx[] = {0, 0, 0, 0, 1, 2, 3, 4};
    return idx[kind];
}

Kind ChoseData::getIdxToKind(u32 player, u32 idx) {
    const Kind kinds0[] = {
        step::hero::KIND_KIRBY_0, step::hero::KIND_META, step::hero::KIND_DEDEDE, step::hero::KIND_DEE, KIND_NONE,
    };
    const Kind kinds1[] = {
        step::hero::KIND_KIRBY_1, step::hero::KIND_META, step::hero::KIND_DEDEDE, step::hero::KIND_DEE, KIND_NONE,
    };
    const Kind kinds2[] = {
        step::hero::KIND_KIRBY_2, step::hero::KIND_META, step::hero::KIND_DEDEDE, step::hero::KIND_DEE, KIND_NONE,
    };
    const Kind kinds3[] = {
        step::hero::KIND_KIRBY_3, step::hero::KIND_META, step::hero::KIND_DEDEDE, step::hero::KIND_DEE, KIND_NONE,
    };
    const Kind* const kinds[] = {kinds0, kinds1, kinds2, kinds3};
    return kinds[player][idx];
}

// Both returns give false in the original: nothing is ever taken for chosen by another player here.
bool ChoseData::chkAllKind(u32 player, Kind kind) {
    for (int i = 0; i < 4; i++) {
        if (player != i && isEntry(i) && kind != KIND_NONE && isDecide(i) && kind == getDecide(i)) {
            return false;
        }
    }
    return false;
}

}
}
}
