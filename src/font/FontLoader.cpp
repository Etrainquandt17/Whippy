#include "font/FontLoader.h"

#include "app/Application.h"
#include "font/FontManager.h"
#include "font/IFont.h"
#include "metafortress.h"
#include "types.h"

namespace font {

#define MF_FUNCTION __ct__Q24font10FontLoaderFQ24font8FontKind
FontLoader::FontLoader(FontKind kind)
    : mKind(kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 base;
    u32 limit;

    hash = 0x811C9E07;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x2427E591
        opword  MF_WORD(0x30)
        opword  0x84B1C580
        opword  0x58635A93
    after1:
        mflr    r18
        lwz     r14, 0x8(r18)
        lwz     r17, 0x0(r18)
        add     r17, r17, r18
        stw     r17, start
        add     r14, r14, r17
        stw     r14, end
        bl      after2
        opword  MF_WORD(0x5C)
        opword  0x58C70551
    after2:
        mflr    r19
        lwz     r29, 0x0(r19)
        stw     r29, expected
    }
    limit = end - start + 1;
    base = start;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001A7;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    while (hash - expected != 0) {
    }
    hel::common::ExplicitSingleton<app::Application>::object_->fontManager().font(mKind).load();
}
#undef MF_FUNCTION

#define MF_FUNCTION __dt__Q24font10FontLoaderFv
FontLoader::~FontLoader() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 addend;
    u32 hash;
    u32 i;
    u32 first;
    u32 limit;

    hash = 0x811C9E29;
    asm {
        bl      after1
        opword  MF_WORD(0x38)
        opword  MF_WORD(0x3C)
        opword  0x9364D002
    after1:
        mflr    r30
        lwz     r21, 0x0(r30)
        lwz     r26, 0x4(r30)
        stw     r26, end
        stw     r21, start
        bl      after2
        opword  MF_WORD(0x5C)
        opword  0x6E96EE13
    after2:
        mflr    r30
        lwz     r20, 0x0(r30)
        stw     r20, expected
    }
    limit = end - start + 1;
    first = start;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x010001AB;
    }
    limit = hash - expected;
    first = limit == 0;
    limit = first >> 5;
    hash = first - limit;
    if (hash == 0) {
        asm {
            bl      after3
            opword  MF_WORD(0xD4)
        after3:
            mflr    r30
            lwz     r25, 0x0(r30)
            stw     r25, -0x4(r1)
            stw     r30, 0x0(r1)
            stw     r25, -0x4(r1)
            stw     r30, -0x8(r1)
            mtlr    r25
            bl      after4
            opword  MF_WORD(0xF8)
            opword  0xD0C46F80
            opword  MF_WORD(0x100)
        after4:
            mflr    r16
            stw     r16, base
            lwz     r18, 0x0(r16)
            stw     r18, offset
            lwz     r28, 0x8(r16)
            stw     r28, addend
        }
        offset = offset + 0x89;
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r27, response
            mtlr    r27
            blr
        }
    } else {
        hel::common::ExplicitSingleton<app::Application>::object_->fontManager().font(mKind).unload();
    }
}
#undef MF_FUNCTION

}  // namespace font
