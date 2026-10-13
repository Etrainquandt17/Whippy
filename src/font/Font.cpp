#include "font/Font.h"

#include "file/FileAccessor.h"
#include "metafortress.h"

namespace font {

Font::Font(const char* path, const char* name)
    : mPath(path)
    , mName(name)
    , mFont()
    , mLoaded(false) {}

Font::~Font() {
    if (mLoaded) {
        Font::unload();
    }
}

#define MF_FUNCTION load__Q24font4FontFv
void Font::load() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 subtrahend;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 response;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    // The starting value is put together in two steps, and its first half sits in the variable of the loop's end.
    last = 0x811D0000;
    hash = last - 0x6225;
    asm {
        bl      stored
        opword  MF_WORD(0x2C)
        opword  0x09171631
    stored:
        mflr    r22
        lwz     r21, 0(r22)
        stw     r21, expected
        bl      ranged
        opword  0x4B0F4B0D
        opword  0x302D3300
        opword  MF_WORD(0x4C)
        opword  MF_WORD(0x50)
        opword  0xA4133590
    ranged:
        mflr    r26
        lwz     r29, 0xC(r26)
        lwz     r27, 8(r26)
        stw     r27, start
        stw     r29, end
    }
    limit = end - start + 1;
    i = 1;
    last = end;
    mFont.SetResource(file::FileAccessor(mPath, false).block().startAddress());
    last -= 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *reinterpret_cast<u16*>(last - i);
        hash *= 0x01000193;
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected == 0) {
        mLoaded = true;
    } else {
        asm {
            bl      located
            opword  MF_WORD(0x114)
        located:
            mflr    r21
            lwz     r26, 0(r21)
            stw     r26, -4(r1)
            stw     r21, 0(r1)
            stw     r26, -4(r1)
            stw     r21, -8(r1)
            mtlr    r26
            bl      based
            opword  MF_WORD(0x138)
            opword  MF_WORD(0x13C)
        based:
            mflr    r25
            lwz     r21, 4(r25)
            stw     r21, subtrahend
            lwz     r21, 0(r25)
            stw     r25, base
            stw     r21, offset
        }
        offset = offset + 0xB5;
        response = offset - subtrahend;
        response = response + base;
        asm {
            lwz     r21, response
            mtlr    r21
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION unload__Q24font4FontFv
void Font::unload() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 addend;
    volatile u32 base;
    volatile u32 response;
    volatile u32 offset;
    u16* word;
    u16* last;
    u32 hash;

    asm {
        bl      stored
        opword  MF_WORD(0x24)
        opword  0x847367F4
    stored:
        mflr    r19
        lwz     r26, 0(r19)
        stw     r26, expected
        bl      ranged
        opword  0xDD061D01
        opword  0x54976E81
        opword  MF_WORD(0x44)
        opword  MF_WORD(0x48)
    ranged:
        mflr    r22
        lwz     r15, 0xC(r22)
        lwz     r25, 8(r22)
        stw     r25, start
        stw     r15, end
    }
    word = reinterpret_cast<u16*>(start);
    last = reinterpret_cast<u16*>(end);
    hash = 0x811C9E07;
    for (;;) {
        if (word == last) {
            break;
        }
        hash ^= *word;
        hash *= 0x010001A7;
        word++;
    }
    hash += hash << 13;
    mFont.RemoveResource();
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected != 0) {
        asm {
            bl      located
            opword  0x69E4020A
            opword  0xE8F01B93
            opword  MF_WORD(0xE0)
        located:
            mflr    r29
            lwz     r24, 8(r29)
            stw     r24, -4(r1)
            stw     r29, 0(r1)
            stw     r24, -4(r1)
            stw     r29, -8(r1)
            mtlr    r24
            bl      based
            opword  MF_WORD(0x104)
            opword  0xE551B40B
            opword  0xE8C6E791
            opword  MF_WORD(0x110)
        based:
            mflr    r20
            stw     r20, base
            lwz     r30, 0(r20)
            stw     r30, offset
            lwz     r21, 0xC(r20)
            stw     r21, addend
        }
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r17, response
            mtlr    r17
            blr
        }
    } else {
        mLoaded = false;
    }
}
#undef MF_FUNCTION

bool Font::loaded() const {
    return mLoaded;
}

const char* Font::name() const {
    return mName;
}

nw4r::ut::Font& Font::font() {
    return mFont;
}

}
