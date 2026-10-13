#define HEL_COMMON_SCOPEDPTR_CONSTRUCTOR_INLINE
#include "scn/subgame/setsuna/info/ResultTargetNumber.h"

#include "lyt/LayoutContext.h"
#include "metafortress.h"
#include "util/StringFormat.h"

namespace scn {
namespace subgame {
namespace setsuna {
namespace info {

ResultTargetNumber::ResultTargetNumber()
    : mLayout(new lyt::Layout(
          lyt::LayoutContext("subgame/setsuna/result/Main", "ResultTargetNumMessage", lyt::LayoutContext::DefaultAllocator()))) {
    initialize();
}

ResultTargetNumber::~ResultTargetNumber() {
}

#define MF_FUNCTION setVisibility__Q53scn7subgame7setsuna4info18ResultTargetNumberFb
void ResultTargetNumber::setVisibility(bool visible) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 response;
    volatile u32 base;
    volatile u32 offset;
    u32 i;
    u32 limit;
    u32 hash;
    bool v;
    ResultTargetNumber* self;
    u32 t;
    u32 last;

    self = this;
    v = visible;
    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x10BC9180
        opword  0x849C0980
        opword  MF_WORD(0x38)
        opword  0x0329870F
    after1:
        mflr    r25
        lwz     r26, 0x0(r25)
        lwz     r16, 0xc(r25)
        add     r26, r26, r25
        add     r16, r16, r26
        stw     r26, start
        stw     r16, end
    }
    t = start;
    last = end;
    last = last - t;
    limit = last + 1;
    i = 1;
    last = end;
    asm {
        bl      after2
        opword  MF_WORD(0x78)
        opword  0x9C33DC76
    after2:
        mflr    r15
        lwz     r22, 0x0(r15)
        stw     r22, expected
    }
    last = last - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        t = last - i;
        t = *(u16*)t;
        hash += t;
        t = hash << 10;
        hash += t;
        t = hash >> 6;
        hash ^= t;
        i += 2;
    }
    limit = hash << 3;
    hash += limit;
    limit = hash >> 11;
    hash ^= limit;
    limit = hash << 15;
    hash += limit;
    limit = expected;
    hash = hash - limit;
    if (hash != 0) {
        asm {
            bl      after3
            opword  0x6C6FBA09
            opword  MF_WORD(0xEC)
        after3:
            mflr    r25
            lwz     r16, 0x4(r25)
            stw     r16, -0x4(r1)
            stw     r25, 0x0(r1)
            stw     r16, -0x4(r1)
            stw     r25, -0x8(r1)
            mtlr    r16
            bl      after4
            opword  MF_WORD(0x110)
            opword  0xB0B1B090
            opword  MF_WORD(0x118)
        after4:
            mflr    r20
            lwz     r26, 0x8(r20)
            stw     r26, key
            lwz     r26, 0x0(r20)
            stw     r20, base
            stw     r26, offset
        }
        offset = offset ^ 0xCA;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r27, response
            mtlr    r27
            blr
        }
    } else {
        self->mLayout->rootPane().setVisibility(v);
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION open__Q53scn7subgame7setsuna4info18ResultTargetNumberFUlUl
void ResultTargetNumber::open(u32 number, u32 last) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 tail;
    u32 size;
    u32 base;
    u32 i;

    hash = 0x811C9DC5;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x80AB1581
        opword  0x6C64B580
        opword  MF_WORD(0x38)
        opword  0x6E71CA06
    after1:
        mflr    r27
        lwz     r21, 0x0(r27)
        lwz     r24, 0xc(r27)
        add     r24, r21, r24
        stw     r21, start
        stw     r24, end
    }
    setVisibility(true);
    size = end - start;
    tail = end;
    asm {
        bl      after2
        opword  MF_WORD(0x78)
        opword  0x799ED5DA
    after2:
        mflr    r24
        lwz     r14, 0x0(r24)
        stw     r14, expected
    }
    i = -1;
    base = tail - 1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(base - i);
        hash *= 0x01000181;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected == 0 && number == last) {
        mLayout->play("FadeInLast");
    } else {
        char name[9];
        util::StringFormat(name, sizeof(name), "FadeIn%02d", last);
        mLayout->play(name);
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION close__Q53scn7subgame7setsuna4info18ResultTargetNumberFv
void ResultTargetNumber::close() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 key;
    volatile u32 base;
    u32 t;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  0xF3B27C08
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
    after1:
        mflr    r25
        lwz     r17, 0x8(r25)
        lwz     r18, 0x4(r25)
        stw     r18, start
        stw     r17, end
    }
    t = start;
    last = end;
    last = last - t;
    limit = last + 1;
    last = end;
    hash = 0;
    i = -1;
    last = last - 1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash *= 193;
        t = last - i;
        t = *(u16*)t;
        hash += t;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x88)
        opword  0x2FB36299
    after2:
        mflr    r16
        lwz     r25, 0x0(r16)
        stw     r25, expected
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash -= expected;
    if (hash != 0) {
        asm {
            bl      after3
            opword  MF_WORD(0xC8)
        after3:
            mflr    r24
            lwz     r28, 0x0(r24)
            stw     r28, -0x4(r1)
            stw     r24, 0x0(r1)
            stw     r28, -0x4(r1)
            stw     r24, -0x8(r1)
            mtlr    r28
            bl      after4
            opword  MF_WORD(0xEC)
            opword  0x4C0CC480
            opword  MF_WORD(0xF4)
        after4:
            mflr    r17
            lwz     r18, 0x0(r17)
            lwz     r26, 0x8(r17)
            stw     r26, key
            stw     r18, offset
            stw     r17, base
        }
        response = offset - key;
        response = response + base;
        asm {
            lwz     r24, response
            mtlr    r24
            blr
        }
    } else {
        setVisibility(false);
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION initialize__Q53scn7subgame7setsuna4info18ResultTargetNumberFv
void ResultTargetNumber::initialize() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 base;
    volatile u32 key;
    u32 hash;
    u32 i;
    u32 first;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x80563E93
        opword  MF_WORD(0x2C)
        opword  0x68312D90
    after1:
        mflr    r22
        lwz     r15, 0x0(r22)
        add     r15, r15, r22
        stw     r15, start
        lwz     r18, 0x8(r22)
        add     r15, r15, r18
        stw     r15, end
    }
    hash = 0x811C9E53;
    limit = end - start + 1;
    first = start;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x010001D1;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x9C)
        opword  0xEEEB67D5
    after2:
        mflr    r24
        lwz     r28, 0x0(r24)
        stw     r28, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if ((hash ^ expected) != 0) {
        asm {
            bl      after3
            opword  0x48A31193
            opword  MF_WORD(0xF0)
        after3:
            mflr    r17
            lwz     r18, 0x4(r17)
            stw     r18, -0x4(r1)
            stw     r17, 0x0(r1)
            stw     r18, -0x4(r1)
            stw     r17, -0x8(r1)
            mtlr    r18
            bl      after4
            opword  MF_WORD(0x114)
            opword  0xB8184392
            opword  MF_WORD(0x11C)
        after4:
            mflr    r17
            lwz     r29, 0x8(r17)
            stw     r29, key
            lwz     r29, 0x0(r17)
            stw     r17, base
            stw     r29, offset
        }
        offset = offset ^ 0x2E;
        response = offset + key;
        response = response + base;
        asm {
            lwz     r17, response
            mtlr    r17
            blr
        }
    } else {
        setVisibility(false);
    }
}
#undef MF_FUNCTION

}
}
}
}
