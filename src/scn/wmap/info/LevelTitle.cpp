#include "scn/wmap/info/LevelTitle.h"

#include "app/Message.h"
#include "lyt/LayoutContext.h"
#include "metafortress.h"
#include "util/ObjList.h"

namespace scn {
namespace wmap {
namespace info {

LevelTitle::LevelTitle(mem::IAllocator& allocator, const lyt::PaneAccessor& parent)
    : mLayout(lyt::LayoutContext("wmap/Main", "LevelTitle", allocator))
    , mMapKind(MAP_KIND_0)
    , mState(1)
    , mTextState(0)
    , mTextType(TEXT_TYPE_0)
    , _1A0(false)
    , _1A1(false) {
    mLayout.setParent(parent);
    mLayout.play("end");
    mLayout.setFrameToTail();
    mLayout.reflectFrameToAnim();
    mTextState = 0;
}

void LevelTitle::updateFrame() {
    mLayout.updateFrame();
    if (mState == 0) {
        if (mLayout.isAnimEnd()) {
            if (_1A1) {
                mfTextOpen();
            }
            mState = 1;
        }
    } else {
        switch (mTextState) {
        case 0:
            if (_1A0 || _1A1) {
                mfTextOpen();
            }
            break;
        case 1:
            if (mLayout.isAnimEnd()) {
                mLayout.setAnimByName("wait");
                mLayout.start(true);
                mTextState = 2;
            }
            break;
        case 2:
            if (_1A0 || !_1A1) {
                mfTextClose();
            }
            break;
        case 3:
            if (mLayout.isAnimEnd()) {
                mTextState = 0;
            }
            break;
        }
    }
    mfUpdateVisibility();
}

void LevelTitle::setMapKind(MapKind kind) {
    mMapKind = kind;
    switch (kind) {
    case MAP_KIND_0:
        mLayout.paneByName("TitleText").setText(app::Message::TextWMap("PopStar"));
        mLayout.paneByName("TitleTextSh").setText(app::Message::TextWMap("PopStar"));
        break;
    case MAP_KIND_1:
        mLayout.paneByName("TitleText").setText(app::Message::TextWMap("Halcandra"));
        mLayout.paneByName("TitleTextSh").setText(app::Message::TextWMap("Halcandra"));
        break;
    }
}

#define MF_FUNCTION isOpen__Q43scn4wmap4info10LevelTitleCFv
bool LevelTitle::isOpen() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 response;
    volatile u32 base;
    u32 hash;
    u32 word;
    u32 last;

    hash = 0xB3;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
    after1:
        mflr    r24
        lwz     r16, 0x0(r24)
        add     r16, r16, r24
        stw     r16, start
        bl      after2
        opword  MF_WORD(0x40)
        opword  0x9D849008
    after2:
        mflr    r24
        lwz     r25, 0x0(r24)
        add     r16, r16, r25
        stw     r16, end
    }
    last = end;
    word = start;
    for (;;) {
        if (word == last) {
            break;
        }
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
        word += 2;
    }
    asm {
        bl      after3
        opword  MF_WORD(0x88)
        opword  0xFF21A20D
    after3:
        mflr    r18
        lwz     r22, 0x0(r18)
        stw     r22, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    hash ^= expected;
    if (hash != 0) {
        asm {
            bl      after4
            opword  0x180AD480
            opword  0xCC0DE793
            opword  0x0AAA1209
            opword  MF_WORD(0xE4)
        after4:
            mflr    r16
            lwz     r29, 0xC(r16)
            stw     r29, -0x4(r1)
            stw     r16, 0x0(r1)
            stw     r29, -0x4(r1)
            stw     r16, -0x8(r1)
            mtlr    r29
            bl      after5
            opword  MF_WORD(0x108)
            opword  MF_WORD(0x10C)
        after5:
            mflr    r17
            lwz     r18, 0x4(r17)
            stw     r18, key
            lwz     r18, 0x0(r17)
            stw     r17, base
            stw     r18, offset
        }
        offset = offset ^ 0x82;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r15, response
            mtlr    r15
            blr
        }
    } else {
        return mState == 1 && mfIsTextBusy();
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION setTextType__Q43scn4wmap4info10LevelTitleFQ53scn4wmap4info10LevelTitle8TextType
void LevelTitle::setTextType(TextType type) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 base;
    u32 limit;

    hash = 0x811C9DDB;
    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0x70E64980
        opword  0x4C5D0F02
        opword  MF_WORD(0x3C)
        opword  0xB35B6D0B
        opword  0x38CF5F80
    after1:
        mflr    r19
        lwz     r25, 0x0(r19)
        add     r25, r25, r19
        stw     r25, start
        lwz     r29, 0xc(r19)
        add     r25, r25, r29
        stw     r25, end
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000193;
        i += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    asm {
        bl      after2
        opword  MF_WORD(0xB8)
        opword  0xFE0670B3
    after2:
        mflr    r27
        lwz     r24, 0x0(r27)
        stw     r24, expected
    }
    hash += hash << 15;
    if (hash - expected != 0 || mTextType != type) {
        mTextType = type;
        _1A0 = true;
    }
}
#undef MF_FUNCTION

void LevelTitle::textOpen(TextType type) {
    setTextType(type);
    _1A1 = true;
}

void LevelTitle::textClose() {
    _1A1 = false;
}

void LevelTitle::open() {
    mLayout.setAnimByName("Unlock");
    mLayout.start(false);
}

#define MF_FUNCTION mfSetText__Q43scn4wmap4info10LevelTitleFv
void LevelTitle::mfSetText() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 response;
    u32 size;
    u32 i;
    u32 first;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0x08728092
        opword  MF_WORD(0x38)
        opword  0xC2ECD104
        opword  0x98D05C81
    after1:
        mflr    r17
        lwz     r16, 0x8(r17)
        lwz     r18, 0x0(r17)
        add     r18, r18, r17
        stw     r18, start
        add     r16, r16, r18
        stw     r16, end
    }
    size = end - start;
    first = start;
    asm {
        bl      after2
        opword  MF_WORD(0x74)
        opword  0x5D053085
    after2:
        mflr    r16
        lwz     r17, 0x0(r16)
        stw     r17, expected
    }
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash += *(u16*)(first + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash = (hash & ~expected) | (expected & ~hash);
    hash = __cntlzw(hash);
    first = hash >> 5;
    hash = first >> 4;
    hash = first - hash;
    if (hash == 0) {
        asm {
            bl      after3
            opword  0x68B09380
            opword  0x80FDAA80
            opword  MF_WORD(0xF4)
        after3:
            mflr    r18
            lwz     r16, 0x8(r18)
            stw     r16, -0x4(r1)
            stw     r18, 0x0(r1)
            stw     r16, -0x4(r1)
            stw     r18, -0x8(r1)
            mtlr    r16
            bl      after4
            opword  MF_WORD(0x118)
            opword  MF_WORD(0x11C)
        after4:
            mflr    r26
            lwz     r18, 0x0(r26)
            stw     r26, base
            lwz     r27, 0x4(r26)
            stw     r18, offset
            stw     r27, key
        }
        offset = offset + 0xA6;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r17, response
            mtlr    r17
            blr
        }
    } else {
        if (mTextType == TEXT_TYPE_0) {
            mLayout.paneByName("AllSphereText").setText(app::Message::TextWMap("SphereNumDisplay"));
            mLayout.paneByName("AllSphereTextSh").setText(app::Message::TextWMap("SphereNumDisplay"));
        } else if (mMapKind == MAP_KIND_0) {
            mLayout.paneByName("AllSphereText").setText(app::Message::TextWMap("ToHalcandraDisplay"));
            mLayout.paneByName("AllSphereTextSh").setText(app::Message::TextWMap("ToHalcandraDisplay"));
        } else {
            mLayout.paneByName("AllSphereText").setText(app::Message::TextWMap("ToPopstarDisplay"));
            mLayout.paneByName("AllSphereTextSh").setText(app::Message::TextWMap("ToPopstarDisplay"));
        }
    }
}
#undef MF_FUNCTION

void LevelTitle::mfUpdateVisibility() {
    switch (mMapKind) {
    case MAP_KIND_0:
        mLayout.paneByName("PopStarIconN").setVisibility(true);
        mLayout.paneByName("HalcandraIconN").setVisibility(false);
        break;
    case MAP_KIND_1:
        mLayout.paneByName("PopStarIconN").setVisibility(false);
        mLayout.paneByName("HalcandraIconN").setVisibility(true);
        break;
    }
}

#define MF_FUNCTION mfTextOpen__Q43scn4wmap4info10LevelTitleFv
void LevelTitle::mfTextOpen() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 response;
    u32 hash;
    u32 i;
    u32 limit;
    u32 last;

    hash = 0x811C9DC5;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x48FBCE1D
    after1:
        mflr    r27
        lwz     r29, 0x0(r27)
        stw     r29, expected
        bl      after2
        opword  MF_WORD(0x44)
        opword  0xFF355006
        opword  MF_WORD(0x4C)
    after2:
        mflr    r21
        lwz     r14, 0x8(r21)
        lwz     r25, 0x0(r21)
        add     r25, r25, r21
        stw     r25, start
        add     r14, r14, r25
        stw     r14, end
    }
    if (mTextState == 0) {
        mfSetText();
        _1A0 = false;
        mLayout.setAnimByName("start");
        mLayout.start(false);
    }
    i = 1;
    last = end;
    limit = last - start + 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x01000181;
        i += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if ((hash ^ expected) != 0) {
        asm {
            bl      after3
            opword  MF_WORD(0x10C)
        after3:
            mflr    r22
            lwz     r16, 0x0(r22)
            stw     r16, -0x4(r1)
            stw     r22, 0x0(r1)
            stw     r16, -0x4(r1)
            stw     r22, -0x8(r1)
            mtlr    r16
            bl      after4
            opword  MF_WORD(0x130)
            opword  MF_WORD(0x134)
        after4:
            mflr    r23
            lwz     r18, 0x0(r23)
            lwz     r19, 0x4(r23)
            stw     r19, key
            stw     r18, offset
            stw     r23, base
        }
        offset = offset - 0xB4;
        response = offset + key;
        response = response + base;
        asm {
            lwz     r27, response
            mtlr    r27
            blr
        }
    } else {
        mTextState = 1;
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION mfTextClose__Q43scn4wmap4info10LevelTitleFv
void LevelTitle::mfTextClose() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 key;
    u32 first;
    u32 limit;
    u32 hash;
    u32 i;

    hash = 0x811C9DC5;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x20596E80
        opword  MF_WORD(0x34)
    after1:
        mflr    r14
        lwz     r25, 0x0(r14)
        lwz     r23, 0x8(r14)
        add     r25, r25, r14
        add     r23, r23, r25
        stw     r25, start
        stw     r23, end
    }
    if (mTextState == 2) {
        mLayout.setAnimByName("end");
        mLayout.start(false);
    }
    limit = end - start + 1;
    first = start;
    asm {
        bl      after2
        opword  MF_WORD(0x90)
        opword  0x7FBE1EAB
    after2:
        mflr    r20
        lwz     r24, 0x0(r20)
        stw     r24, expected
    }
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x01000181;
    }
    hash = expected ^ hash;
    hash += hash * 12;
    if (hash == 0) {
        mTextState = 3;
    } else {
        asm {
            bl      after3
            opword  0x34C3A180
            opword  MF_WORD(0xFC)
        after3:
            mflr    r17
            lwz     r20, 0x4(r17)
            stw     r20, -0x4(r1)
            stw     r17, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r17, -0x8(r1)
            mtlr    r20
            bl      after4
            opword  MF_WORD(0x120)
            opword  0xA4FE4F92
            opword  0x30C00893
            opword  MF_WORD(0x12C)
        after4:
            mflr    r19
            lwz     r28, 0xC(r19)
            stw     r28, key
            lwz     r28, 0x0(r19)
            stw     r19, base
            stw     r28, offset
        }
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r17, response
            mtlr    r17
            blr
        }
    }
}
#undef MF_FUNCTION

}}}  // namespace scn::wmap::info
