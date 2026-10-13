#include "scn/arena/ArenaData.h"

#include "app/Random.h"
#include "hel/common/ExplicitSingleton.h"
#include "hid/HIDManager.h"
#include "metafortress.h"

using scn::step::hero::AbilityKind;
using scn::step::hero::Kind;

namespace scn {
namespace arena {

namespace {

// TODO: the enumerator; it stands for no ability.
const AbilityKind T_ABILITY_NONE = static_cast<AbilityKind>(35);

// TODO: the enumerator; it stands for no boss.
const int T_BOSS_NONE = 0x1C;

}

struct BossInfo {
    int mBossId;
    int mMapKind;
};

extern const BossInfo ARENA_BOSS_TBL[13] = {
    { 0, 0x139 }, { 1, 0x13A }, { 2, 0x13B }, { 3, 0x13C }, { 4, 0x13D },  { 5, 0x13E },  { 6, 0x13F },
    { 7, 0x140 }, { 8, 0x141 }, { 9, 0x142 }, { 10, 0x143 }, { 11, 0x144 }, { 12, 0x145 },
};

extern const BossInfo ARENAEX_BOSS_TBL[15] = {
    { 13, 0x149 }, { 14, 0x14A }, { 15, 0x14B }, { 16, 0x14C }, { 17, 0x14D }, { 18, 0x14E }, { 19, 0x14F }, { 20, 0x150 },
    { 21, 0x151 }, { 22, 0x152 }, { 23, 0x153 }, { 24, 0x156 }, { 25, 0x157 }, { 26, 0x154 }, { 27, 0x155 },
};

extern const AbilityKind ARENA_ABILITY_TBL[20] = {
    static_cast<AbilityKind>(1),  static_cast<AbilityKind>(2),  static_cast<AbilityKind>(3),  static_cast<AbilityKind>(4),
    static_cast<AbilityKind>(5),  static_cast<AbilityKind>(6),  static_cast<AbilityKind>(7),  static_cast<AbilityKind>(8),
    static_cast<AbilityKind>(9),  static_cast<AbilityKind>(11), static_cast<AbilityKind>(12), static_cast<AbilityKind>(13),
    static_cast<AbilityKind>(14), static_cast<AbilityKind>(15), static_cast<AbilityKind>(16), static_cast<AbilityKind>(17),
    static_cast<AbilityKind>(18), static_cast<AbilityKind>(19), static_cast<AbilityKind>(20), static_cast<AbilityKind>(21),
};

ArenaData::Player ArenaData::Player::Create() {
    static Player player;
    for (u32 i = 0; i < 4; i++) {
        player.mEntries[i].mIsEntry = false;
        player.mEntries[i].mKind = static_cast<Kind>(i);
        player.mEntries[i].mAbility = step::hero::ABILITY_KIND_NORMAL;
    }
    player.mNum = 1;
    player.mEntries[0].mIsEntry = true;
    return player;
}

void ArenaData::Player::setEntryInfo(seq::EntryInfo info) {
    mNum = 0;
    for (u32 i = 0; i < 4; i++) {
        if (info._0[i] <= step::hero::KIND_DEE) {
            mNum++;
            mEntries[i].mIsEntry = true;
            mEntries[i].mKind = static_cast<Kind>(info._0[i]);
            switch (mEntries[i].mKind) {
            case step::hero::KIND_KIRBY_0:
            case step::hero::KIND_KIRBY_1:
            case step::hero::KIND_KIRBY_2:
            case step::hero::KIND_KIRBY_3:
                mEntries[i].mAbility = step::hero::ABILITY_KIND_NORMAL;
                break;
            case step::hero::KIND_META:
                mEntries[i].mAbility = step::hero::ABILITY_KIND_META;
                break;
            case step::hero::KIND_DEDEDE:
                mEntries[i].mAbility = step::hero::ABILITY_KIND_DEDEDE;
                break;
            case step::hero::KIND_DEE:
                mEntries[i].mAbility = step::hero::ABILITY_KIND_DEE;
                break;
            }
        } else {
            mEntries[i].mIsEntry = false;
            mEntries[i].mKind = static_cast<Kind>(i);
            mEntries[i].mAbility = step::hero::ABILITY_KIND_NORMAL;
        }
    }
}

seq::EntryInfo ArenaData::Player::getEntryInfo() {
    seq::EntryInfo info;
    info._0[0] = 0;
    for (u32 i = 1; i < 4; i++) {
        if (mEntries[i].mIsEntry) {
            info._0[i] = mEntries[i].mKind;
        } else {
            info._0[i] = step::hero::KIND_NONE;
        }
    }
    return info;
}

void ArenaData::Player::reset(u32 index) {
    if (!hel::common::ExplicitSingleton<hid::HIDManager>::object_->gameWR(index).isConnected()) {
        mEntries[index].mIsEntry = false;
        mEntries[index].mKind = static_cast<Kind>(index);
        mEntries[index].mAbility = step::hero::ABILITY_KIND_NORMAL;
    }
}

ArenaData::Item ArenaData::Item::Create(storage::ArenaGameKind kind) {
    static Item itemData;
    itemData.reset(kind);
    return itemData;
}

#define MF_FUNCTION reset__Q43scn5arena9ArenaData4ItemFQ27storage13ArenaGameKind
void ArenaData::Item::reset(storage::ArenaGameKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
    after1:
        mflr    r21
        lwz     r16, 0x0(r21)
        add     r16, r16, r21
        stw     r16, start
        bl      after2
        opword  0xE4D51690
        opword  0xBA6A2603
        opword  MF_WORD(0x48)
    after2:
        mflr    r21
        lwz     r24, 0x8(r21)
        add     r16, r16, r24
        stw     r16, end
        bl      after3
        opword  MF_WORD(0x60)
        opword  0xEF1D6940
    after3:
        mflr    r16
        lwz     r17, 0x0(r16)
        stw     r17, expected
    }
    mTomatoNum = 0;
    hash = 0xB5;
    base = start;
    limit = end - base + 1;
    switch (kind) {
    case storage::ARENA_GAME_KIND_0:
        mTomatoNum = 4;
        break;
    case storage::ARENA_GAME_KIND_1:
        mTomatoNum = 2;
        break;
    }
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash = (hash << 4 ^ hash >> 28) ^ *(u16*)(base + i - 1);
    }
    hash += hash << 3;
    for (u32 n = 0; n < mTomatoNum; n++) {
        switch (kind) {
        case storage::ARENA_GAME_KIND_0:
        case storage::ARENA_GAME_KIND_1:
            mTomatoRemainders[n] = ITEM_REMAINDER_2;
            break;
        }
    }
    hash ^= hash >> 11;
    hash += hash << 15;
    hash ^= expected;
    if (hash != 0) {
        volatile u32 response;
        volatile u32 base2;
        volatile u32 addend;
        volatile u32 offset;

        asm {
            bl      after4
            opword  0x87E9D206
            opword  MF_WORD(0x158)
        after4:
            mflr    r18
            lwz     r26, 0x4(r18)
            stw     r26, -0x4(r1)
            stw     r18, 0x0(r1)
            stw     r26, -0x4(r1)
            stw     r18, -0x8(r1)
            mtlr    r26
            bl      after5
            opword  MF_WORD(0x17C)
            opword  0xF8B6A493
            opword  0x6CCBFB80
            opword  MF_WORD(0x188)
        after5:
            mflr    r28
            lwz     r29, 0xc(r28)
            stw     r29, addend
            lwz     r29, 0x0(r28)
            stw     r28, base2
            stw     r29, offset
        }
        offset = offset + 0x7B;
        response = offset - addend;
        response = response + base2;
        asm {
            lwz     r30, response
            mtlr    r30
            blr
        }
    } else {
        mBoxState = BOX_STATE_3;
    }
}
#undef MF_FUNCTION

void ArenaData::Item::setTomatoRemainder(u32 index, ItemRemainder remainder) {
    mTomatoRemainders[index] = remainder;
}

ArenaData::ItemRemainder ArenaData::Item::getTomatoRemainder(u32 index) const {
    return mTomatoRemainders[index];
}

void ArenaData::Item::updateTomatoRemainder(u32 index) {
    if (mTomatoRemainders[index] > ITEM_REMAINDER_0) {
        mTomatoRemainders[index] = static_cast<ItemRemainder>(mTomatoRemainders[index] - 1);
    }
}

void ArenaData::Item::setBoxState(BoxState state) {
    if (mBoxState >= BOX_STATE_1 && mBoxState <= BOX_STATE_3 && state >= BOX_STATE_0 && state <= BOX_STATE_3) {
        mBoxState = state;
    }
}

ArenaData::BossSet ArenaData::BossSet::Create(storage::ArenaGameKind kind) {
    static BossSet bossSetData = {};
    bossSetData.reset(kind);
    return bossSetData;
}

int ArenaData::BossSet::mapKind() const {
    return mBosses[mIndex].mMapKind;
}

void ArenaData::BossSet::next() {
    if (!isEnd()) {
        mIndex++;
    }
}

bool ArenaData::BossSet::isEnd() const {
    return chkEnd(mIndex);
}

bool ArenaData::BossSet::isNextEnd() const {
    return chkEnd(mIndex + 1);
}

bool ArenaData::BossSet::isRoom2() const {
    return chkRoom2(mIndex);
}

bool ArenaData::BossSet::isNextRoom2() const {
    return chkRoom2(mIndex + 1);
}

int ArenaData::BossSet::getBossId() const {
    return mBosses[mIndex].mBossId;
}

AbilityKind ArenaData::BossSet::getAbilityKind(u32 index) const {
    return mBosses[mIndex].mAbilities[index];
}

AbilityKind ArenaData::BossSet::getNextAbilityKind(u32 index) const {
    return mBosses[mIndex + 1].mAbilities[index];
}

#define MF_FUNCTION reset__Q43scn5arena9ArenaData7BossSetFQ27storage13ArenaGameKind
void ArenaData::BossSet::reset(storage::ArenaGameKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 last;
    u32 limit;
    u32 t;
    u32 first;
    const BossInfo* tbl;
    int pos;
    u32 lastId;
    int num;

    t = 0x811D0000;
    hash = t - 0x61F9;
    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0x64B27493
        opword  MF_WORD(0x38)
        opword  0x20D62381
        opword  0x7C2A4A81
    after1:
        mflr    r27
        lwz     r18, 0x8(r27)
        lwz     r23, 0x0(r27)
        add     r18, r23, r18
        stw     r18, end
        stw     r23, start
    }
    mAbilityIndex = 0;
    limit = end - start + 1;
    i = 1;
    last = end;
    for (u32 n = 0; n < 6; n++) {
        mAbilities[n] = T_ABILITY_NONE;
    }
    mIndex = 0;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001A7;
        i += 2;
    }
    mNum = 0;
    asm {
        bl      after2
        opword  MF_WORD(0xD8)
        opword  0x6C7D2352
    after2:
        mflr    r18
        lwz     r27, 0x0(r18)
        stw     r27, expected
    }
    for (u32 n = 0; n < 16; n++) {
        mBosses[n].mBossId = T_BOSS_NONE;
        mBosses[n].mMapKind = 0x2B8;
        for (u32 k = 0; k < 2; k++) {
            mBosses[n].mAbilities[k] = T_ABILITY_NONE;
        }
    }
    first = T_BOSS_NONE;
    lastId = T_BOSS_NONE;
    tbl = 0;
    pos = 0;
    hash ^= hash >> 10;
    switch (kind) {
    case storage::ARENA_GAME_KIND_0:
        mNum = 13;
        tbl = ARENA_BOSS_TBL;
        first = 0;
        lastId = 9;
        break;
    case storage::ARENA_GAME_KIND_1:
        mNum = 15;
        tbl = ARENAEX_BOSS_TBL;
        first = 13;
        lastId = 22;
        break;
    }
    hash ^= hash << 20;
    num = lastId - first + 1;
    first = expected;
    lastId = hash & ~first;
    first = expected;
    first = first & ~hash;
    first = lastId | first;
    first = __cntlzw(first);
    lastId = first >> 5;
    first = lastId << 2;
    hash = lastId | first;
    if (hash == 0) {
        volatile u32 addend;
        volatile u32 response;
        volatile u32 offset;
        volatile u32 base2;

        asm {
            stw     r21, -0x4(r1)
            bl      after3
            opword  MF_WORD(0x1E0)
        after3:
            mflr    r21
            lwz     r16, 0x0(r21)
            stw     r16, 0x0(r1)
            stw     r21, 0x4(r1)
            mtlr    r16
            bl      after4
            opword  MF_WORD(0x1FC)
            opword  0x28CFDB91
            opword  0x7C9F0F91
            opword  MF_WORD(0x208)
        after4:
            mflr    r24
            lwz     r18, 0xc(r24)
            stw     r18, addend
            lwz     r18, 0x0(r24)
            stw     r24, base2
            stw     r18, offset
        }
        offset = offset - 0xA0;
        response = offset + addend;
        response = response + base2;
        asm {
            lwz     r25, response
            mtlr    r25
            blr
        }
    } else if (num != 0) {
        for (int n = 0; n < num; n++) {
            int count = app::Random::Rand(num - n) + 1;
            do {
                pos++;
                pos %= num;
                if (mBosses[pos].mBossId == T_BOSS_NONE) {
                    count--;
                }
            } while (count > 0);
            mBosses[pos].mBossId = tbl[n].mBossId;
            mBosses[pos].mMapKind = tbl[n].mMapKind;
            for (int k = 0; k < 2; k++) {
                mBosses[pos].mAbilities[k] = getNextAbility();
            }
        }
        for (; num < mNum; num++) {
            mBosses[num].mBossId = tbl[num].mBossId;
            mBosses[num].mMapKind = tbl[num].mMapKind;
            for (int k = 0; k < 2; k++) {
                mBosses[num].mAbilities[k] = getNextAbility();
            }
        }
        if (kind == storage::ARENA_GAME_KIND_1) {
            for (u32 n = 0; n < mNum; n++) {
                int index = app::Random::Rand(2);
                mBosses[n].mAbilities[index] = step::hero::ABILITY_KIND_SLEEP;
            }
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION getNextAbility__Q43scn5arena9ArenaData7BossSetFv
AbilityKind ArenaData::BossSet::getNextAbility() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 hash;
    u32 last;
    u32 limit;
    u32 count;
    u32 num;
    int index;
    AbilityKind candidates[20];

    hash = 0;
    for (u32 n = 0; n < 20; n++) {
        candidates[n] = T_ABILITY_NONE;
    }
    count = 0;
    num = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x50)
        opword  0x2A936608
    after1:
        mflr    r17
        lwz     r19, 0x0(r17)
        stw     r19, expected
    }
    for (int n = 0; n < 20; n++) {
        if (!useAbility(ARENA_ABILITY_TBL[n])) {
            candidates[num++] = ARENA_ABILITY_TBL[n];
            count++;
        }
    }
    asm {
        bl      after2
        opword  0x0C034300
        opword  MF_WORD(0xBC)
    after2:
        mflr    r16
        lwz     r21, 0x4(r16)
        stw     r21, start
        bl      after3
        opword  MF_WORD(0xD0)
        opword  0xB42B9304
    after3:
        mflr    r16
        lwz     r21, 0x0(r16)
        stw     r21, end
    }
    last = end;
    limit = last - start + 1;
    index = app::Random::Rand(count);
    setAbility(candidates[index]);
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash *= 193;
        hash += *(u16*)(last - 1 - i);
    }
    last = expected;
    limit = hash & ~last;
    last = expected;
    last = last & ~hash;
    last = limit | last;
    last = __cntlzw(last);
    limit = last >> 5;
    last = limit << 9;
    hash = limit | last;
    if (hash == 0) {
        return candidates[index];
    }
    volatile u32 base2;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 addend;

    asm {
        bl      after4
        opword  0xC86BBB93
        opword  0xF0EFC193
        opword  MF_WORD(0x184)
    after4:
        mflr    r30
        lwz     r15, 0x8(r30)
        stw     r15, -0x4(r1)
        stw     r30, 0x0(r1)
        stw     r15, -0x4(r1)
        stw     r30, -0x8(r1)
        mtlr    r15
        bl      after5
        opword  MF_WORD(0x1A8)
        opword  0xDCB96681
        opword  MF_WORD(0x1B0)
    after5:
        mflr    r16
        lwz     r24, 0x8(r16)
        stw     r24, addend
        lwz     r24, 0x0(r16)
        stw     r16, base2
        stw     r24, offset
    }
    offset = offset - 0x59;
    response = offset - addend;
    response = response + base2;
    asm {
        lwz     r28, response
        mtlr    r28
        blr
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION setAbility__Q43scn5arena9ArenaData7BossSetFQ43scn4step4hero11AbilityKind
void ArenaData::BossSet::setAbility(AbilityKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0x6695B463
    after1:
        mflr    r29
        lwz     r25, 0x0(r29)
        stw     r25, expected
        bl      after2
        opword  MF_WORD(0x38)
        opword  0x38EC8791
        opword  0x94A7FA91
        opword  MF_WORD(0x44)
        opword  0x018E7507
    after2:
        mflr    r21
        lwz     r19, 0x0(r21)
        lwz     r16, 0xc(r21)
        add     r19, r19, r21
        add     r16, r16, r19
        stw     r19, start
        stw     r16, end
    }
    hash = 0x811C9DC5;
    limit = end - start + 1;
    base = start;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000181;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    while (hash - expected != 0) {
    }
    mAbilities[mAbilityIndex] = kind;
    mAbilityIndex = (mAbilityIndex + 1) % 6;
}
#undef MF_FUNCTION

bool ArenaData::BossSet::useAbility(AbilityKind kind) {
    for (u32 i = 0; i < 6; i++) {
        if (kind == mAbilities[i]) {
            return true;
        }
    }
    return false;
}

bool ArenaData::BossSet::chkEnd(u32 index) const {
    if (getBossId() == T_BOSS_NONE) {
        return true;
    }
    return index >= mNum;
}

bool ArenaData::BossSet::chkRoom2(u32 index) const {
    return mBosses[index].mBossId >= 23;
}

ArenaData ArenaData::Create(storage::ArenaGameKind kind) {
    static ArenaData data = {};
    data.mGameKind = kind;
    data.mTime = 0;
    for (u32 i = 0; i < 7; i++) {
        data.mHp[i] = 0;
    }
    for (u32 i = 0; i < 2; i++) {
        data.mHpRatio[i] = 1.0f;
    }
    data.mPlayer = Player::Create();
    data.mItem = Item::Create(kind);
    data.mBossSet = BossSet::Create(kind);
    return data;
}

#define MF_FUNCTION reset__Q33scn5arena9ArenaDataFv
void ArenaData::reset() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  MF_WORD(0x28)
        opword  0x3D73B401
        opword  0x3C0D4F92
    after1:
        mflr    r19
        lwz     r28, 0x0(r19)
        add     r28, r28, r19
        stw     r28, start
        lwz     r22, 0x4(r19)
        add     r28, r28, r22
        stw     r28, end
    }
    hash = 0x811C9DDB;
    mTime = 0;
    limit = end - start + 1;
    base = start;
    mItem.reset(gameKind());
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000193;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xB8)
        opword  0xE636C766
    after2:
        mflr    r26
        lwz     r25, 0x0(r26)
        stw     r25, expected
    }
    limit = expected;
    hash = hash - limit;
    if (hash == 0) {
        mBossSet.reset(gameKind());
    } else {
        volatile u32 base2;
        volatile u32 response;
        volatile u32 addend;
        volatile u32 offset;

        asm {
            bl      after3
            opword  MF_WORD(0xF8)
            opword  0x2CE92981
            opword  0x8CA44D90
        after3:
            mflr    r22
            addi    r15, r22, 0x18
            mtlr    r15
            lwz     r14, 0x0(r22)
            stw     r14, -0x4(r1)
            stw     r15, 0x0(r1)
            stw     r22, 0x4(r1)
            blrl
            bl      after4
            opword  MF_WORD(0x128)
            opword  0x1C968B93
            opword  0x94C1C480
            opword  MF_WORD(0x134)
        after4:
            mflr    r30
            stw     r30, base2
            lwz     r17, 0x0(r30)
            stw     r17, offset
            lwz     r19, 0xc(r30)
            stw     r19, addend
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

#define MF_FUNCTION gameKind__Q33scn5arena9ArenaDataCFv
storage::ArenaGameKind ArenaData::gameKind() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 last;
    u32 limit;

    hash = 0;
    asm {
        bl      after1
        opword  0x28ABB891
        opword  MF_WORD(0x2C)
        opword  0x781B8680
        opword  MF_WORD(0x34)
        opword  0xA8A6D490
        opword  0xB422240B
    after1:
        mflr    r29
        lwz     r24, 0x4(r29)
        lwz     r25, 0xc(r29)
        stw     r25, end
        stw     r24, start
    }
    limit = end - start + 1;
    i = 1;
    last = end;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash += *(u16*)(last - 1 - i);
        hash += hash << 10;
        hash ^= hash >> 6;
        i += 2;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xA0)
        opword  0xCAF1E431
    after2:
        mflr    r27
        lwz     r30, 0x0(r27)
        stw     r30, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash -= expected;
    hash += hash * 46;
    if (hash == 0) {
        return mGameKind;
    }
    volatile u32 response;
    volatile u32 base2;
    volatile u32 offset;
    volatile u32 addend;

    asm {
        bl      after3
        opword  0x24AE5D80
        opword  MF_WORD(0xEC)
    after3:
        mflr    r24
        lwz     r25, 0x4(r24)
        stw     r25, -0x4(r1)
        stw     r24, 0x0(r1)
        stw     r25, -0x4(r1)
        stw     r24, -0x8(r1)
        mtlr    r25
        bl      after4
        opword  MF_WORD(0x110)
        opword  0xA4E4B590
        opword  MF_WORD(0x118)
    after4:
        mflr    r15
        lwz     r27, 0x8(r15)
        stw     r27, addend
        lwz     r27, 0x0(r15)
        stw     r15, base2
        stw     r27, offset
    }
    response = offset - addend;
    response = response + base2;
    asm {
        lwz     r15, response
        mtlr    r15
        blr
    }
}
#undef MF_FUNCTION

void ArenaData::setTime(u32 time) {
    if (time > 359999) {
        time = 359999;
    }
    mTime = time;
}

u32 ArenaData::getTime() const {
    return mTime;
}

void ArenaData::incTime() {
    if (mTime < 359999) {
        mTime++;
    }
}

void ArenaData::setHpRatio(u32 index, f32 ratio) {
    if (index >= 2) {
        index = 1;
    }
    mHpRatio[index] = ratio;
}

f32 ArenaData::getHpRatio(u32 index) {
    if (index >= 2) {
        index = 1;
    }
    return mHpRatio[index];
}

void ArenaData::setHp(Kind kind, u32 hp) {
    if (kind >= step::hero::KIND_KIRBY_0 && kind <= step::hero::KIND_DEE) {
        mHp[kind] = hp;
    }
}

u32 ArenaData::getHp(Kind kind) {
    u32 hp = 0;
    if (kind >= step::hero::KIND_KIRBY_0 && kind <= step::hero::KIND_DEE) {
        hp = mHp[kind];
    }
    return hp;
}

bool ArenaData::isHpReady() {
    u32 sum = 0;
    for (u32 i = 0; i < 7; i++) {
        sum += mHp[i];
    }
    return sum != 0;
}

}
}
