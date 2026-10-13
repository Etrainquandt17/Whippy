#include "scn/step/debug/ObjInfoRepos.h"

#include "metafortress.h"

namespace scn {
namespace step {
namespace debug {

#define MF_FUNCTION __dt__Q43scn4step5debug12ObjInfoReposFv
ObjInfoRepos::~ObjInfoRepos() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0x25948967
    after1:
        mflr    r14
        lwz     r29, 0x0(r14)
        stw     r29, expected
        bl      after2
        opword  MF_WORD(0x48)
    after2:
        mflr    r23
        lwz     r18, 0x0(r23)
        stw     r18, start
        bl      after3
        opword  0x6CD9F180
        opword  MF_WORD(0x60)
        opword  0xA4A78B80
    after3:
        mflr    r23
        lwz     r29, 0x4(r23)
        add     r29, r29, r18
        stw     r29, end
    }
    hash = 0x811C9DDB;
    base = start;
    limit = end - base + 1;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000193;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    while (hash - expected != 0) {
    }
}
#undef MF_FUNCTION

void ObjInfoRepos::registerObj(const IObjInfoImpl& obj) {
    mObjs.add(&obj);
}

#define MF_FUNCTION unregisterObj__Q43scn4step5debug12ObjInfoReposFRCQ43scn4step5debug12IObjInfoImpl
void ObjInfoRepos::unregisterObj(const IObjInfoImpl& obj) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 base;
    volatile u32 key;
    u32 hash;
    u32 word;
    u32 last;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x8BB50DE8
    after1:
        mflr    r22
        lwz     r25, 0x0(r22)
        stw     r25, expected
    }
    hash = 0x811C9E53;
    asm {
        bl      after2
        opword  MF_WORD(0x48)
        opword  0xF0B8E280
    after2:
        mflr    r26
        lwz     r24, 0x0(r26)
        add     r24, r24, r26
        stw     r24, start
        bl      after3
        opword  0x541BF480
        opword  MF_WORD(0x68)
        opword  0xAC2E7E81
    after3:
        mflr    r26
        lwz     r16, 0x4(r26)
        add     r24, r24, r16
        stw     r24, end
    }
    word = start;
    last = end;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash ^= *(u16*)word;
        hash *= 0x010001D1;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash == expected) {
        mObjs.erase(mObjs.find(&obj));
    } else {
        asm {
            bl      after4
            opword  0x78224B81
            opword  0x4B46FA05
            opword  MF_WORD(0x180)
        after4:
            mflr    r20
            lwz     r21, 0x8(r20)
            stw     r21, -0x4(r1)
            stw     r20, 0x0(r1)
            stw     r21, -0x4(r1)
            stw     r20, -0x8(r1)
            mtlr    r21
            bl      after5
            opword  MF_WORD(0x1A4)
            opword  MF_WORD(0x1A8)
        after5:
            mflr    r21
            lwz     r18, 0x0(r21)
            lwz     r15, 0x4(r21)
            stw     r15, key
            stw     r18, offset
            stw     r21, base
        }
        offset = offset ^ 0x9A;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r16, response
            mtlr    r16
            blr
        }
    }
}
#undef MF_FUNCTION

}
}
}
