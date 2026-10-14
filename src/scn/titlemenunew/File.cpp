#include "scn/titlemenunew/File.h"

#include "app/BackupFileAccessor.h"
#include "app/Message.h"
#include "hel/debug/Print.h"
#include "lyt/LayoutContext.h"
#include "metafortress.h"
#include "util/ObjList.h"

using app::BackupFileAccessor;
using app::Message;
using hel::debug::Print;

namespace {

bool isExtra(u32 file) {
    BackupFileAccessor accessor(file);
    return accessor.extraModeOpened();
}

}

namespace scn {
namespace titlemenunew {

#define MF_FUNCTION __ct__Q33scn12titlemenunew4FileFRQ23mem10IAllocatorRCQ23lyt12PaneAccessorQ43scn12titlemenunew4File2NoRQ24info10AnimSyncer
File::File(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, No no, info::AnimSyncer& animSyncer)
    : mLayout(lyt::LayoutContext("titlemenunew/Main", isExtra(no) ? "FileExtra" : "FileNormal", allocator))
    , mIcon(allocator, mLayout.pane("KirbyIconN"))
    , mStatus(allocator, mLayout.pane("StatusNormalN"), false, isExtra(no) ? FileStatus::KIND_1 : FileStatus::KIND_0, no, animSyncer)
    , mStatusExtra(allocator, isExtra(no) ? mLayout.pane("StatusExtraN") : mLayout.rootPane(), false, FileStatus::KIND_2, no, animSyncer)
    , mCompleteMark(allocator, mLayout.pane("CrownN"), animSyncer)
    , mIsExtra(isExtra(no))
    , mSE() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 base;

    asm {
        bl      after1
        opword  0xD8B10C91
        opword  MF_WORD(0x1C0)
        opword  0x84F01090
        opword  MF_WORD(0x1C8)
        opword  0xD6E23608
    after1:
        mflr    r28
        lwz     r19, 0x4(r28)
        lwz     r18, 0xc(r28)
        stw     r19, end
        stw     r18, start
    }
    mLayout.setParent(parent);
    mLayout.pane("FileN").setText(Message::TextTitleMenu("File"));
    // Bound to a reference so that it is a compiler temporary. As a named local it
    // lands in another saved register, in every order of the declarations.
    const u32& size = end - start;
    base = start;
    hash = 0;
    mLayout.pane("FileNumber").setText(Print::HelSPrintfImpl("%u", no + 1));
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash *= 37;
        hash += *(u16*)(base + i - 1);
    }
    mIcon.update(no);
    asm {
        bl      after2
        opword  MF_WORD(0x2A8)
        opword  0x7175134D
    after2:
        mflr    r24
        lwz     r21, 0x0(r24)
        stw     r21, expected
    }
    hash += hash << 3;
    if (BackupFileAccessor(no).completed()) {
        mCompleteMark.show();
    }
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected == 0 && !isExtra(no)) {
        mStatusExtra.hide();
    }
    mStatus.deselect();
    mStatusExtra.deselect();
}
#undef MF_FUNCTION

void File::updateFrame() {
    mLayout.updateFrame();
    mIcon.updateFrame();
    mStatus.updateFrame();
    mStatusExtra.updateFrame();
    mCompleteMark.updateFrame();
}

void File::appear() {
    mLayout.play("OpenSmall");
}

#define MF_FUNCTION showSelected__Q33scn12titlemenunew4FileFv
void File::showSelected() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 base;
    u32 size;
    u32 hash;
    u32 i;
    File* self;

    // A copy of this in a local: without it this takes a saved register above the check's.
    self = this;
    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  MF_WORD(0x28)
        opword  0x65465307
    after1:
        mflr    r30
        lwz     r29, 0x0(r30)
        lwz     r27, 0x4(r30)
        add     r29, r29, r30
        add     r27, r27, r29
        stw     r29, start
        stw     r27, end
    }
    base = start;
    size = end - base;
    self->appearSelected();
    hash = 0x811C9E53;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001D1;
    }
    self->mLayout.setFrameToTail();
    asm {
        bl      after2
        opword  MF_WORD(0xA4)
        opword  0x0CC40F64
    after2:
        mflr    r24
        lwz     r21, 0x0(r24)
        stw     r21, expected
    }
    size = hash >> 10;
    hash ^= size;
    size = hash << 20;
    hash ^= size;
    size = expected;
    size = size & ~hash;
    base = expected;
    hash = hash & ~base;
    hash = size | hash;
    base = hash >> 4;
    hash = hash - base;
    if (hash == 0) {
        self->mLayout.reflectFrameToAnim();
    } else {
        volatile u32 base2;
        volatile u32 response;
        volatile u32 offset;
        volatile u32 addend;

        asm {
            bl      after3
            opword  0x1789500D
            opword  0x98F48392
            opword  MF_WORD(0x104)
        after3:
            mflr    r21
            lwz     r14, 0x8(r21)
            stw     r14, -0x4(r1)
            stw     r21, 0x0(r1)
            stw     r14, -0x4(r1)
            stw     r21, -0x8(r1)
            mtlr    r14
            bl      after4
            opword  MF_WORD(0x128)
            opword  0x14FEE193
            opword  0x38672793
            opword  MF_WORD(0x134)
        after4:
            mflr    r27
            lwz     r26, 0x0(r27)
            stw     r27, base2
            lwz     r25, 0xc(r27)
            stw     r26, offset
            stw     r25, addend
        }
        offset = offset - 0xE7;
        response = offset + addend;
        response = response + base2;
        asm {
            lwz     r23, response
            mtlr    r23
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION appearSelected__Q33scn12titlemenunew4FileFv
void File::appearSelected() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 base;
    u32 last;
    u32 hash;
    u32 i;
    u32 limit;

    hash = 0;
    asm {
        bl      after1
        opword  0x5B7C7207
        opword  0x18397F80
        opword  MF_WORD(0x30)
        opword  0x419E3C03
        opword  0x7809A980
        opword  MF_WORD(0x3C)
        opword  0x048C4893
    after1:
        mflr    r22
        lwz     r17, 0x14(r22)
        stw     r17, end
        lwz     r19, 0x8(r22)
        stw     r19, start
    }
    limit = end - start + 1;
    i = 1;
    last = end;
    select();
    base = last - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        last = base - i;
        last = *(u16*)last;
        hash += last;
        last = hash << 10;
        hash += last;
        last = hash >> 6;
        hash ^= last;
        i += 2;
    }
    last = hash >> 10;
    hash ^= last;
    last = hash << 20;
    hash ^= last;
    asm {
        bl      after2
        opword  MF_WORD(0xBC)
        opword  0xE26F62EF
    after2:
        mflr    r29
        lwz     r22, 0x0(r29)
        stw     r22, expected
    }
    last = expected;
    last = last & ~hash;
    base = expected;
    base = hash & ~base;
    hash = last | base;
    base = hash << 4;
    hash = hash | base;
    if (hash == 0) {
        mLayout.play("OpenBig");
    } else {
        volatile u32 response;
        volatile u32 base2;
        volatile u32 offset;
        volatile u32 addend;

        asm {
            bl      after3
            opword  0x9CFECA92
            opword  0x931D4E0B
            opword  MF_WORD(0x110)
        after3:
            mflr    r29
            lwz     r24, 0x8(r29)
            stw     r24, -0x4(r1)
            stw     r29, 0x0(r1)
            stw     r24, -0x4(r1)
            stw     r29, -0x8(r1)
            mtlr    r24
            bl      after4
            opword  MF_WORD(0x134)
            opword  0xBC85570E
            opword  0xA2875803
            opword  MF_WORD(0x140)
        after4:
            mflr    r28
            stw     r28, base2
            lwz     r14, 0x0(r28)
            stw     r14, offset
            lwz     r19, 0xc(r28)
            stw     r19, addend
        }
        offset = offset + 0x1D;
        response = offset + addend;
        response = response + base2;
        asm {
            lwz     r17, response
            mtlr    r17
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION hide__Q33scn12titlemenunew4FileFv
void File::hide() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 last;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xA75B37E2
    after1:
        mflr    r30
        lwz     r27, 0x0(r30)
        stw     r27, expected
        bl      after2
        opword  MF_WORD(0x3C)
        opword  0xD4B06D91
        opword  0x6CCB6392
        opword  MF_WORD(0x48)
        opword  0x506DC991
    after2:
        mflr    r28
        lwz     r18, 0xc(r28)
        stw     r18, end
        lwz     r15, 0x0(r28)
        stw     r15, start
    }
    hash = 0xB3;
    disappear();
    word = start;
    last = end;
    for (; word != last; word += 2) {
        hash = *(u16*)word ^ (hash << 4 ^ hash >> 28);
    }
    mLayout.setFrameToTail();
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected != 0) {
        volatile u32 addend;
        volatile u32 response;
        volatile u32 base2;
        volatile u32 offset;

        asm {
            bl      after3
            opword  0x100DCF90
            opword  MF_WORD(0xD4)
        after3:
            mflr    r28
            lwz     r19, 0x4(r28)
            stw     r19, -0x4(r1)
            stw     r28, 0x0(r1)
            stw     r19, -0x4(r1)
            stw     r28, -0x8(r1)
            mtlr    r19
            bl      after4
            opword  MF_WORD(0xF8)
            opword  0x50AE9D92
            opword  MF_WORD(0x100)
        after4:
            mflr    r26
            stw     r26, base2
            lwz     r18, 0x0(r26)
            stw     r18, offset
            lwz     r19, 0x8(r26)
            stw     r19, addend
        }
        offset = offset + 0x40;
        addend = 0;
        response = offset;
        response = response + base2;
        asm {
            lwz     r18, response
            mtlr    r18
            blr
        }
    } else {
        mLayout.reflectFrameToAnim();
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION disappear__Q33scn12titlemenunew4FileFv
void File::disappear() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 value;
    u32 base;
    u32 hash;
    u32 limit;

    hash = 0;
    asm {
        bl      after1
        opword  0x84D94892
        opword  0x499A020B
        opword  MF_WORD(0x30)
        opword  0xC3CA5701
        opword  0x0C464092
        opword  MF_WORD(0x3C)
        opword  0x14129380
    after1:
        mflr    r17
        lwz     r15, 0x8(r17)
        lwz     r21, 0x14(r17)
        stw     r21, end
        stw     r15, start
    }
    i = start;
    value = end;
    value = value - i;
    limit = value + 1;
    i = 1;
    base = start;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash = hash * 61;
        value = base + i;
        value = *(u16*)(value - 1);
        hash = hash + value;
        i = i + 2;
    }
    value = hash >> 10;
    hash ^= value;
    value = hash << 20;
    hash ^= value;
    asm {
        bl      after2
        opword  MF_WORD(0xA4)
        opword  0xC2189102
    after2:
        mflr    r24
        lwz     r20, 0x0(r24)
        stw     r20, expected
    }
    value = expected;
    value = value & ~hash;
    i = expected;
    i = hash & ~i;
    hash = value | i;
    i = hash * 19;
    hash = hash + i;
    if (hash == 0) {
        mLayout.play("Close");
    } else {
        volatile u32 base2;
        volatile u32 response;
        volatile u32 addend;
        volatile u32 offset;

        asm {
            bl      after3
            opword  MF_WORD(0xF0)
        after3:
            mflr    r24
            lwz     r20, 0x0(r24)
            stw     r20, -0x4(r1)
            stw     r24, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r24, -0x8(r1)
            mtlr    r20
            bl      after4
            opword  MF_WORD(0x114)
            opword  0xFCA23491
            opword  0x301F2392
            opword  MF_WORD(0x120)
        after4:
            mflr    r29
            stw     r29, base2
            lwz     r15, 0x0(r29)
            stw     r15, offset
            lwz     r27, 0xc(r29)
            stw     r27, addend
        }
        offset = offset + 0x85;
        response = offset ^ addend;
        response = response + base2;
        asm {
            lwz     r19, response
            mtlr    r19
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION select__Q33scn12titlemenunew4FileFv
void File::select() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 last;
    u32 value;

    hash = 0;
    mLayout.play("Focus");
    asm {
        bl      after1
        opword  0x78285280
        opword  MF_WORD(0x34)
        opword  0x8B0C120F
        opword  0x88B51280
        opword  MF_WORD(0x40)
    after1:
        mflr    r26
        lwz     r29, 0x10(r26)
        lwz     r16, 0x4(r26)
        stw     r16, start
        stw     r29, end
        bl      after2
        opword  MF_WORD(0x5C)
        opword  0x40C74F14
    after2:
        mflr    r16
        lwz     r15, 0x0(r16)
        stw     r15, expected
    }
    mLayout.pane("Black").setVisibility(false);
    last = end;
    word = start;
    for (;;) {
        if (word == last) {
            break;
        }
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
        word += 2;
    }
    hash += hash << 13;
    mStatus.select();
    hash ^= hash >> 7;
    hash += hash << 3;
    mStatusExtra.select();
    value = hash >> 17;
    hash ^= value;
    value = hash << 5;
    hash += value;
    value = expected;
    hash ^= value;
    if (hash != 0) {
        volatile u32 offset;
        volatile u32 response;
        volatile u32 base2;
        volatile u32 addend;

        asm {
            bl      after3
            opword  MF_WORD(0x114)
        after3:
            mflr    r25
            lwz     r20, 0x0(r25)
            stw     r20, -0x4(r1)
            stw     r25, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r25, -0x8(r1)
            mtlr    r20
            bl      after4
            opword  MF_WORD(0x138)
            opword  MF_WORD(0x13C)
        after4:
            mflr    r22
            lwz     r29, 0x4(r22)
            stw     r29, addend
            lwz     r29, 0x0(r22)
            stw     r22, base2
            stw     r29, offset
        }
        offset = offset + 0x93;
        addend = 0;
        response = offset;
        response = response + base2;
        asm {
            lwz     r20, response
            mtlr    r20
            blr
        }
    } else {
        mCompleteMark.select();
    }
}
#undef MF_FUNCTION

void File::deselect() {
    mLayout.play("UnFocus");
    mLayout.pane("Black").setVisibility(true);
    mStatus.deselect();
    mStatusExtra.deselect();
    mCompleteMark.deselect();
}

void File::unlockExtra() {
    mStatusExtra.unlock();
}

}}  // namespace scn::titlemenunew
