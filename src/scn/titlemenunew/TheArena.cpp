#include "scn/titlemenunew/TheArena.h"

#include "app/BackupFileAccessor.h"
#include "lyt/LayoutContext.h"
#include "metafortress.h"
#include "util/ObjList.h"

using app::BackupFileAccessor;

namespace scn {
namespace titlemenunew {

#define MF_FUNCTION \
    __ct__Q33scn12titlemenunew8TheArenaFRQ23mem10IAllocatorRCQ23lyt12PaneAccessorQ43scn12titlemenunew8TheArena4KindRQ24info10AnimSyncer
namespace {

const char* tClearMarkPaneName(TheArena::Kind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    const char* name;
    u32 hash;
    u32 t;
    u32 i;
    u32 limit;
    u32 last;

    asm {
        bl      after1
        opword  MF_WORD(0x6C)
        opword  0x98FC120B
        opword  0x1CE14C80
        opword  MF_WORD(0x78)
        opword  0x0CF25280
        opword  0xD449E901
    after1:
        mflr    r20
        lwz     r23, 0x0(r20)
        lwz     r27, 0xc(r20)
        add     r23, r23, r20
        add     r27, r27, r23
        stw     r23, start
        stw     r27, end
    }
    hash = 0;
    i = 1;
    last = end;
    t = start;
    t = last - t;
    limit = t + 1;
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
        opword  MF_WORD(0xEC)
        opword  0xD555C7A4
    after2:
        mflr    r15
        lwz     r16, 0x0(r15)
        stw     r16, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if ((hash ^ expected) != 0) {
        volatile u32 base2;
        volatile u32 response;
        volatile u32 addend;
        volatile u32 offset;

        asm {
            stw     r15, -0x4(r1)
            bl      after3
            opword  MF_WORD(0x128)
            opword  0xF883B280
            opword  0x82343E01
        after3:
            mflr    r15
            lwz     r20, 0x0(r15)
            stw     r20, 0x0(r1)
            stw     r15, 0x4(r1)
            mtlr    r20
            bl      after4
            opword  MF_WORD(0x14C)
            opword  0x56F0DA00
            opword  MF_WORD(0x154)
        after4:
            mflr    r19
            lwz     r23, 0x8(r19)
            stw     r23, addend
            lwz     r23, 0x0(r19)
            stw     r19, base2
            stw     r23, offset
        }
        addend = 0;
        response = offset;
        response = response + base2;
        asm {
            lwz     r23, response
            mtlr    r23
            blr
        }
    } else {
        switch (kind) {
        case TheArena::KIND_0:
            name = "ClearMarkN0";
            break;
        case TheArena::KIND_1:
            name = "ClearMarkN1";
            break;
        case TheArena::KIND_2:
            name = "SinClearMarkN";
            break;
        default:
            name = "";
            break;
        }
    }
    return name;
}

}

TheArena::TheArena(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, Kind kind, info::AnimSyncer& animSyncer)
    : mKind(kind)
    , mLayout(lyt::LayoutContext("titlemenunew/Main", "Kakutou", allocator))
    , mClearMark(allocator, mLayout.pane(tClearMarkPaneName(kind)), animSyncer) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 last;

    asm {
        bl      after5
        opword  0x9C6ED380
        opword  0x047C7381
        opword  MF_WORD(0x21C)
    after5:
        mflr    r19
        lwz     r16, 0x8(r19)
        stw     r16, start
        bl      after6
        opword  0xDC1BE490
        opword  MF_WORD(0x234)
        opword  0x54031893
    after6:
        mflr    r19
        lwz     r22, 0x4(r19)
        add     r22, r22, r16
        stw     r22, end
    }
    mLayout.setParent(parent);
    mLayout.pane("KakutouN0").hide();
    asm {
        bl      after7
        opword  MF_WORD(0x280)
        opword  0x5CBAAB93
    after7:
        mflr    r15
        lwz     r17, 0x0(r15)
        stw     r17, expected
    }
    mLayout.pane("KakutouN1").hide();
    hash = 0xC5;
    mLayout.pane("ShinKakutouN").hide();
    word = start;
    last = end;
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
    }
    switch (kind) {
    case KIND_0:
        mLayout.pane("KakutouN0").show();
        break;
    case KIND_1:
        mLayout.pane("KakutouN1").show();
        break;
    case KIND_2:
        mLayout.pane("ShinKakutouN").show();
        break;
    default:
        while (hash - expected != 0) {
        }
        break;
    }
    updateClearMark();
}
#undef MF_FUNCTION

void TheArena::updateFrame() {
    mLayout.updateFrame();
    mClearMark.updateFrame();
}

#define MF_FUNCTION updateClearMark__Q33scn12titlemenunew8TheArenaFv
void TheArena::updateClearMark() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    BackupFileAccessor accessor;
    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0x28BD0A8D
    after1:
        mflr    r30
        lwz     r26, 0x0(r30)
        stw     r26, expected
        bl      after2
        opword  MF_WORD(0x48)
        opword  0x64177A93
        opword  MF_WORD(0x50)
        opword  0x583F6E0C
    after2:
        mflr    r23
        lwz     r26, 0x0(r23)
        lwz     r14, 0x8(r23)
        stw     r14, end
        stw     r26, start
    }
    mClearMark.hide();
    limit = end - start;
    last = end;
    i = -1;
    while (i != limit - 1) {
        i += 2;
        hash += *(u16*)(last - 1 - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash -= expected;
    if (hash == 0) {
        switch (mKind) {
        case KIND_0:
        case KIND_1:
            if (accessor.theArenaState() == 3 && accessor.theArenaCharaState() != storage::UNLOCK_STATE_LOCKED) {
                mClearMark.show(ClearMark::KIND_2);
            }
            break;
        case KIND_2:
            if (accessor.theArenaExtraState() == 3 &&
                accessor.theArenaExtraCharaState() != storage::UNLOCK_STATE_LOCKED) {
                mClearMark.show(ClearMark::KIND_3);
            }
            break;
        }
    } else {
        volatile u32 response;
        volatile u32 offset;
        volatile u32 base2;
        volatile u32 addend;

        asm {
            bl      after3
            opword  0x401C2993
            opword  MF_WORD(0x150)
        after3:
            mflr    r24
            lwz     r26, 0x4(r24)
            stw     r26, -0x4(r1)
            stw     r24, 0x0(r1)
            stw     r26, -0x4(r1)
            stw     r24, -0x8(r1)
            mtlr    r26
            bl      after4
            opword  MF_WORD(0x174)
            opword  0x3E5C0F0D
            opword  0xFAE54602
            opword  MF_WORD(0x180)
        after4:
            mflr    r15
            lwz     r18, 0x0(r15)
            stw     r15, base2
            lwz     r21, 0xc(r15)
            stw     r18, offset
            stw     r21, addend
        }
        offset = offset ^ 0xC;
        response = offset ^ addend;
        response = response + base2;
        asm {
            lwz     r15, response
            mtlr    r15
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION show__Q33scn12titlemenunew8TheArenaFv
void TheArena::show() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 limit;
    u32 hash;
    u32 t;
    u32 last;
    u32 i;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xF573F86A
    after1:
        mflr    r25
        lwz     r18, 0x0(r25)
        stw     r18, expected
    }
    hash = 0;
    asm {
        bl      after2
        opword  0xFCB9A407
        opword  MF_WORD(0x44)
        opword  0x3C921881
        opword  0xBEC0FA03
        opword  MF_WORD(0x50)
    after2:
        mflr    r22
        lwz     r19, 0x10(r22)
        stw     r19, start
        lwz     r21, 0x4(r22)
        stw     r21, end
    }
    t = start;
    last = end;
    last = last - t;
    limit = last + 1;
    i = 1;
    last = end;
    last = last - 1;
    for (; i != limit; i += 2) {
        hash *= 151;
        t = last - i;
        t = *(u16*)t;
        hash += t;
    }
    limit = hash << 3;
    hash += limit;
    limit = hash >> 11;
    hash ^= limit;
    limit = hash << 15;
    hash += limit;
    limit = expected;
    hash ^= limit;
    if (hash != 0) {
        volatile u32 offset;
        volatile u32 response;
        volatile u32 base2;
        volatile u32 addend;

        asm {
            stw     r29, -0x4(r1)
            bl      after3
            opword  MF_WORD(0xD4)
            opword  0x48263F91
            opword  0x28DDFE93
            opword  0x8DAB1605
        after3:
            mflr    r29
            lwz     r20, 0x0(r29)
            stw     r20, 0x0(r1)
            stw     r29, 0x4(r1)
            mtlr    r20
            bl      after4
            opword  MF_WORD(0xFC)
            opword  MF_WORD(0x100)
        after4:
            mflr    r24
            lwz     r20, 0x4(r24)
            stw     r20, addend
            lwz     r20, 0x0(r24)
            stw     r24, base2
            stw     r20, offset
        }
        offset = offset ^ 0x7B;
        addend = 0;
        response = offset;
        response = response + base2;
        asm {
            lwz     r17, response
            mtlr    r17
            blr
        }
    } else {
        mLayout.rootPane().show();
    }
}
#undef MF_FUNCTION

// TODO: the original ranks this behind the hash, like a local declared after it. self = this is merged with this
// here and ranks first, so the copy is written as an instruction. Without a copy and with the check in natural
// expressions, this and the hash are right and the multiplier and the loop's temporary trade registers.
#define MF_FUNCTION hide__Q33scn12titlemenunew8TheArenaFv
void TheArena::hide() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    register TheArena* self;
    u32 w;
    u32 last;
    u32 t;
    u32 i;
    u32 limit;

    asm { mr self, r3 }
    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x18491A81
        opword  0x24BCC991
        opword  MF_WORD(0x30)
        opword  0x0DDA9709
    after1:
        mflr    r24
        lwz     r22, 0x0(r24)
        lwz     r26, 0xc(r24)
        add     r26, r22, r26
        stw     r22, start
        stw     r26, end
    }
    t = 0x811D0000;
    hash = t - 0x61F9;
    asm {
        bl      after2
        opword  MF_WORD(0x5C)
        opword  0x911E03D6
    after2:
        mflr    r24
        lwz     r25, 0x0(r24)
        stw     r25, expected
    }
    i = 1;
    last = end;
    t = start;
    t = last - t;
    limit = t + 1;
    t = last - 1;
    last = 0x01000000;
    last = last + 0x1A7;
    for (;;) {
        if (i == limit) {
            break;
        }
        w = t - i;
        w = *(u16*)w;
        hash ^= w;
        hash *= last;
        i += 2;
    }
    last = hash << 3;
    hash += last;
    last = hash >> 11;
    hash ^= last;
    last = hash << 15;
    hash += last;
    last = expected;
    last = hash & ~last;
    w = expected;
    w = w & ~hash;
    w = last | w;
    hash = __cntlzw(w);
    w = hash >> 5;
    hash = w >> 3;
    hash = w - hash;
    if (hash == 0) {
        volatile u32 offset;
        volatile u32 addend;
        volatile u32 base2;
        volatile u32 response;

        asm {
            bl      after3
            opword  MF_WORD(0xF8)
        after3:
            mflr    r14
            lwz     r26, 0x0(r14)
            stw     r26, -0x4(r1)
            stw     r14, 0x0(r1)
            stw     r26, -0x4(r1)
            stw     r14, -0x8(r1)
            mtlr    r26
            bl      after4
            opword  MF_WORD(0x11C)
            opword  0x34443D81
            opword  0x6C83DD93
            opword  MF_WORD(0x128)
        after4:
            mflr    r22
            lwz     r14, 0x0(r22)
            stw     r22, base2
            lwz     r29, 0xc(r22)
            stw     r14, offset
            stw     r29, addend
        }
        offset = offset - 0x5C;
        response = offset ^ addend;
        response = response + base2;
        asm {
            lwz     r28, response
            mtlr    r28
            blr
        }
    } else {
        self->mLayout.rootPane().hide();
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION enable__Q33scn12titlemenunew8TheArenaFb
void TheArena::enable(bool flag) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    hash = 0xBF;
    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xA88B6007
        opword  MF_WORD(0x2C)
    after1:
        mflr    r27
        lwz     r16, 0x0(r27)
        add     r16, r16, r27
        lwz     r30, 0x8(r27)
        stw     r16, start
        add     r30, r30, r16
        stw     r30, end
    }
    last = end;
    word = start;
    asm {
        bl      after2
        opword  MF_WORD(0x58)
        opword  0x02A03D61
    after2:
        mflr    r20
        lwz     r29, 0x0(r20)
        stw     r29, expected
    }
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected != 0 || flag) {
        mLayout.play("Enable");
    } else {
        mLayout.play("Disable");
    }
}
#undef MF_FUNCTION

lyt::PaneAccessor TheArena::parent() {
    return mLayout.parent();
}

void TheArena::setParent(const lyt::PaneAccessor& parent) {
    mLayout.unsetParent();
    mLayout.setParent(parent);
}

#define MF_FUNCTION cursorParent__Q33scn12titlemenunew8TheArenaFv
namespace {

const char* tCursorPaneName(TheArena::Kind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    const char* name;
    u32 hash;
    u32 base;
    u32 i;
    u32 limit;

    asm {
        bl      after3
        opword  MF_WORD(0xC8)
        opword  0x969808C3
    after3:
        mflr    r22
        lwz     r27, 0x0(r22)
        stw     r27, expected
    }
    hash = 0;
    asm {
        bl      after4
        opword  MF_WORD(0xE4)
        opword  0x9CA87091
        opword  MF_WORD(0xEC)
    after4:
        mflr    r14
        lwz     r21, 0x0(r14)
        lwz     r24, 0x8(r14)
        add     r24, r21, r24
        stw     r21, start
        stw     r24, end
    }
    base = start;
    limit = end - base + 1;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash += *(u16*)(base + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    if (hash != expected) {
        volatile u32 response;
        volatile u32 base2;
        volatile u32 offset;
        volatile u32 addend;

        asm {
            bl      after5
            opword  0xC97C0903
            opword  0x547CC490
            opword  0xB0192F80
            opword  MF_WORD(0x16C)
        after5:
            mflr    r18
            lwz     r21, 0xc(r18)
            stw     r21, -0x4(r1)
            stw     r18, 0x0(r1)
            stw     r21, -0x4(r1)
            stw     r18, -0x8(r1)
            mtlr    r21
            bl      after6
            opword  MF_WORD(0x190)
            opword  MF_WORD(0x194)
        after6:
            mflr    r22
            stw     r22, base2
            lwz     r26, 0x0(r22)
            stw     r26, offset
            lwz     r19, 0x4(r22)
            stw     r19, addend
        }
        offset = offset ^ 0x31;
        response = offset + addend;
        response = response + base2;
        asm {
            lwz     r19, response
            mtlr    r19
            blr
        }
    } else {
        switch (kind) {
        case TheArena::KIND_0:
            name = "Kakutou0CursorN";
            break;
        case TheArena::KIND_1:
            name = "Kakutou1CursorN";
            break;
        case TheArena::KIND_2:
            name = "SinCursorN";
            break;
        default:
            name = "";
            break;
        }
    }
    return name;
}

}

lyt::PaneAccessor TheArena::cursorParent() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 mult;
    u32 t;
    u32 word;
    u32 last;

    t = 0x811D0000;
    hash = t - 0x61D7;
    asm {
        bl      after1
        opword  MF_WORD(0x38)
        opword  MF_WORD(0x3C)
    after1:
        mflr    r18
        lwz     r16, 0x0(r18)
        lwz     r21, 0x4(r18)
        stw     r16, end
        stw     r21, start
    }
    word = start;
    last = end;
    word -= 2;
    t = 0x01000000;
    mult = t + 0x1AB;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        t = *(u16*)word;
        hash ^= t;
        hash *= mult;
    }
    t = hash >> 10;
    hash ^= t;
    t = hash << 20;
    hash ^= t;
    asm {
        bl      after2
        opword  MF_WORD(0x98)
        opword  0x1BAD78D3
    after2:
        mflr    r24
        lwz     r25, 0x0(r24)
        stw     r25, expected
    }
    if (hash - expected == 0) {
        return mLayout.pane(tCursorPaneName(mKind));
    } else {
        volatile u32 offset;
        volatile u32 response;
        volatile u32 base2;
        volatile u32 addend;

        asm {
            bl      after7
            opword  0xA382330A
            opword  0xA43C1990
            opword  MF_WORD(0x250)
        after7:
            mflr    r21
            lwz     r26, 0x8(r21)
            stw     r26, -0x4(r1)
            stw     r21, 0x0(r1)
            stw     r26, -0x4(r1)
            stw     r21, -0x8(r1)
            mtlr    r26
            bl      after8
            opword  MF_WORD(0x274)
            opword  MF_WORD(0x278)
        after8:
            mflr    r29
            lwz     r17, 0x4(r29)
            stw     r17, addend
            lwz     r17, 0x0(r29)
            stw     r29, base2
            stw     r17, offset
        }
        response = offset ^ addend;
        response = response + base2;
        asm {
            lwz     r26, response
            mtlr    r26
            blr
        }
    }
}
#undef MF_FUNCTION

void TheArena::focus() {
    mLayout.play("Focus");
}

void TheArena::unfocus() {
    mLayout.play("UnFocus");
}

void TheArena::decide() {
    mLayout.play("Decide");
}

void TheArena::unlock() {
    mLayout.play("Unlock");
}

bool TheArena::isAnimEnd() const {
    return mLayout.isAnimEnd();
}

}}  // namespace scn::titlemenunew
