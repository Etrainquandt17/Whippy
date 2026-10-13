#include "info/common/WiiButton.h"

#include "lyt/LayoutContext.h"
#include "metafortress.h"
#include "util/ObjList.h"

namespace info {
namespace common {

WiiButton::WiiButton(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, Kind kind)
    : mLayout(lyt::LayoutContext("common/Main", "WiiButton", allocator))
    , _190(false)
    , _191(false) {
    mLayout.setParent(parent);
    mLayout.pane("Button1N").hide();
    mLayout.pane("Button2N").hide();
    mLayout.pane("ButtonPlusN").hide();
    mLayout.pane("ButtonMinusN").hide();
    mLayout.pane("ButtonAN").hide();
    switch (kind) {
    case KIND_0:
        mLayout.pane("Button1N").show();
        break;
    case KIND_1:
        mLayout.pane("Button2N").show();
        break;
    case KIND_2:
        mLayout.pane("ButtonPlusN").show();
        break;
    case KIND_3:
        mLayout.pane("ButtonMinusN").show();
        break;
    case KIND_4:
        mLayout.pane("ButtonAN").show();
        break;
    }
    mLayout.rootPane().hide();
}

void WiiButton::hide() {
    mLayout.rootPane().hide();
}

void WiiButton::appearWait() {
    mLayout.play("Start", "Wait");
    mLayout.rootPane().show();
    _190 = false;
}

void WiiButton::appearWaitNoShadow() {
    mLayout.play("Wait2");
    mLayout.rootPane().show();
}

#define MF_FUNCTION appearBlink__Q34info6common9WiiButtonFv
void WiiButton::appearBlink() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 addend;
    volatile u32 base;
    volatile u32 response;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;
    u32 word;
    u32 t;
    u32 tail;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  MF_WORD(0x28)
        opword  0xDCCFA592
        opword  0x2882B180
    after1:
        mflr    r22
        lwz     r25, 0x0(r22)
        stw     r25, end
        lwz     r25, 0x4(r22)
        stw     r25, start
    }
    hash = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x50)
        opword  0x0AE6522C
    after2:
        mflr    r30
        lwz     r23, 0x0(r30)
        stw     r23, expected
    }
    mLayout.play("Start", "Blink");
    limit = end - start + 1;
    tail = end;
    i = -1;
    last = tail - 1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash *= 37;
        hash += *(u16*)(last - i);
    }
    hash += hash << 3;
    mLayout.rootPane().show();
    t = hash >> 11;
    hash ^= t;
    t = hash << 15;
    hash += t;
    t = expected;
    t = t & ~hash;
    word = expected;
    word = hash & ~word;
    hash = t | word;
    word = hash >> 6;
    hash = hash - word;
    if (hash == 0) {
        asm {
            stw     r30, -0x4(r1)
            bl      after3
            opword  MF_WORD(0x114)
            opword  0xB891CB92
        after3:
            mflr    r30
            lwz     r23, 0x0(r30)
            stw     r23, 0x0(r1)
            stw     r30, 0x4(r1)
            mtlr    r23
            bl      after4
            opword  MF_WORD(0x134)
            opword  0x133E4201
            opword  MF_WORD(0x13C)
        after4:
            mflr    r20
            lwz     r27, 0x0(r20)
            stw     r20, base
            lwz     r16, 0x8(r20)
            stw     r27, offset
            stw     r16, addend
        }
        offset = offset ^ 0x8E;
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r30, response
            mtlr    r30
            blr
        }
    } else {
        _190 = true;
    }
}
#undef MF_FUNCTION

void WiiButton::disappear() {
    mLayout.play("End");
    mLayout.rootPane().show();
    _190 = false;
}

void WiiButton::wait() {
    mLayout.play("Wait");
    mLayout.rootPane().show();
    _190 = false;
}

#define MF_FUNCTION waitNoShadow__Q34info6common9WiiButtonFv
void WiiButton::waitNoShadow() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 base;
    volatile u32 addend;
    volatile u32 offset;
    u32 i;
    u32 first;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xE5D4CB92
    after1:
        mflr    r29
        lwz     r19, 0x0(r29)
        stw     r19, expected
    }
    hash = 0x811C9E53;
    asm {
        bl      after2
        opword  0x342B5D81
        opword  0xBCAD7681
        opword  MF_WORD(0x4C)
        opword  0x68584992
        opword  MF_WORD(0x54)
        opword  0x5C6D0081
    after2:
        mflr    r16
        lwz     r15, 0x10(r16)
        stw     r15, end
        lwz     r26, 0x8(r16)
        stw     r26, start
    }
    first = start;
    limit = end - first + 1;
    if (!_190) {
        mLayout.play("Wait2");
        mLayout.rootPane().show();
    } else {
        _191 = true;
    }
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x010001D1;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected != 0) {
        asm {
            bl      after3
            opword  0x86173908
            opword  0x20886507
            opword  MF_WORD(0x134)
        after3:
            mflr    r25
            lwz     r24, 0x8(r25)
            stw     r24, -0x4(r1)
            stw     r25, 0x0(r1)
            stw     r24, -0x4(r1)
            stw     r25, -0x8(r1)
            mtlr    r24
            bl      after4
            opword  MF_WORD(0x158)
            opword  0xA8DB0C81
            opword  MF_WORD(0x160)
        after4:
            mflr    r30
            stw     r30, base
            lwz     r14, 0x0(r30)
            stw     r14, offset
            lwz     r17, 0x8(r30)
            stw     r17, addend
        }
        offset = offset ^ 0x1C;
        response = offset - addend;
        response = response + base;
        asm {
            lwz     r20, response
            mtlr    r20
            blr
        }
    } else {
        _190 = false;
    }
}
#undef MF_FUNCTION

void WiiButton::blink() {
    mLayout.play("Blink");
    mLayout.rootPane().show();
    _190 = true;
}

void WiiButton::blink2() {
    mLayout.play("Blink2");
    mLayout.rootPane().show();
    _190 = false;
}

#define MF_FUNCTION push__Q34info6common9WiiButtonFv
void WiiButton::push() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 addend;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 response;
    u16* word;
    u16* last;
    u32 hash;

    asm {
        bl      after1
        opword  0xBF5D7800
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
        opword  0x52325C0A
        opword  0x86BC830A
    after1:
        mflr    r29
        lwz     r16, 0x4(r29)
        lwz     r26, 0x8(r29)
        stw     r16, start
        add     r26, r16, r26
        stw     r26, end
    }
    mLayout.play("Push");
    hash = 0x811C9DC5;
    asm {
        bl      after2
        opword  MF_WORD(0x68)
        opword  0x2CF49C7A
    after2:
        mflr    r19
        lwz     r28, 0x0(r19)
        stw     r28, expected
    }
    word = (u16*)start;
    last = (u16*)end;
    mLayout.rootPane().show();
    for (; word != last; word++) {
        hash ^= *word;
        hash *= 0x01000181;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash ^= expected;
    if (hash == 0) {
        _190 = false;
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0xF8)
        after3:
            mflr    r14
            lwz     r28, 0x0(r14)
            stw     r28, -0x4(r1)
            stw     r14, 0x0(r1)
            stw     r28, -0x4(r1)
            stw     r14, -0x8(r1)
            mtlr    r28
            bl      after4
            opword  MF_WORD(0x11C)
            opword  0xA89FA191
            opword  MF_WORD(0x124)
        after4:
            mflr    r25
            lwz     r26, 0x0(r25)
            stw     r25, base
            lwz     r14, 0x8(r25)
            stw     r26, offset
            stw     r14, addend
        }
        addend = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r17, response
            mtlr    r17
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION hold__Q34info6common9WiiButtonFv
void WiiButton::hold() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 hash;
    u32 base;
    u32 limit;

    asm {
        bl      after1
        opword  0x55561504
        opword  MF_WORD(0x20)
        opword  0xBC92FA91
        opword  MF_WORD(0x28)
    after1:
        mflr    r29
        lwz     r22, 0x4(r29)
        lwz     r28, 0xC(r29)
        add     r28, r22, r28
        stw     r22, start
        stw     r28, end
    }
    hash = 0x811C9DC5;
    mLayout.play("Hold");
    asm {
        bl      after2
        opword  MF_WORD(0x5C)
        opword  0xB2BC2BEA
    after2:
        mflr    r29
        lwz     r20, 0x0(r29)
        stw     r20, expected
    }
    i = 1;
    base = start;
    limit = end - base + 1;
    mLayout.rootPane().show();
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000181;
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    _190 = expected != hash;
}
#undef MF_FUNCTION

void WiiButton::updateFrame() {
    mLayout.updateFrame();
    if (_191) {
        if (static_cast<u32>(mLayout.frame()) % 10 == 0) {
            waitNoShadow();
            _191 = false;
        }
    }
}

void WiiButton::setFrame(f32 frame) {
    mLayout.setFrame(frame);
}

void WiiButton::changeDoLoop(bool doLoop) {
    mLayout.changeDoLoop(doLoop);
}

}}  // namespace info::common
