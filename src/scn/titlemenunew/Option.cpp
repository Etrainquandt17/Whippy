#include "scn/titlemenunew/Option.h"

#include "app/Message.h"
#include "info/AnimSyncer.h"
#include "metafortress.h"

namespace scn {
namespace titlemenunew {

// TODO: the constructor and the six std::tr1 functions it instantiates are not written. It ends in
// mSequence.anim(_194, "CompUnlock").wait(1).call(std::tr1::bind(&Option::complete, this)), and std/tr1/function.h
// cannot make a function from a callable yet. These hold the place of its member pointer constant and of its
// strings in .data, so that the string offsets of the functions below are the original's.
#pragma force_active on
const char* const T_CONSTRUCTOR_PLACE_0 = "\0\0\0\0\0\0\0\0\0\0\0";
const char* const T_CONSTRUCTOR_PLACE_1 = "titlemenunew/Main";
const char* const T_CONSTRUCTOR_PLACE_2 = "OptionBase";
const char* const T_CONSTRUCTOR_PLACE_3 = "CompUnlock";
#pragma force_active off

void Option::updateFrame() {
    mLayout.updateFrame();
    _194.updateFrame();
    mSequence.update();
}

#define MF_FUNCTION enable__Q33scn12titlemenunew6OptionFb
void Option::enable(bool flag) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x5BFDABF7
    after1:
        mflr    r19
        lwz     r25, 0x0(r19)
        stw     r25, expected
    }
    hash = 0;
    mAnimSyncer->remove(_194);
    asm {
        bl      after2
        opword  MF_WORD(0x50)
        opword  MF_WORD(0x54)
        opword  0x78607380
    after2:
        mflr    r15
        lwz     r19, 0x0(r15)
        add     r19, r19, r15
        lwz     r17, 0x4(r15)
        stw     r19, start
        add     r17, r17, r19
        stw     r17, end
    }
    i = 1;
    last = end;
    limit = last - start + 1;
    for (; i != limit; i += 2) {
        hash += *(u16*)(last - 1 - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    selectPanel(static_cast<Kind>(_324), false);
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash != expected) {
        volatile u32 offset;
        volatile u32 addend;
        volatile u32 response;
        volatile u32 base2;

        asm {
            bl      after3
            opword  0x20C00D80
            opword  0x68916280
            opword  0x04515480
            opword  MF_WORD(0xF8)
        after3:
            mflr    r25
            lwz     r19, 0xc(r25)
            stw     r19, -0x4(r1)
            stw     r25, 0x0(r1)
            stw     r19, -0x4(r1)
            stw     r25, -0x8(r1)
            mtlr    r19
            bl      after4
            opword  MF_WORD(0x11C)
            opword  MF_WORD(0x120)
        after4:
            mflr    r16
            lwz     r19, 0x0(r16)
            stw     r16, base2
            lwz     r17, 0x4(r16)
            stw     r19, offset
            stw     r17, addend
        }
        offset = offset + 0x5F;
        addend = 0;
        response = offset;
        response = response + base2;
        asm {
            lwz     r26, response
            mtlr    r26
            blr
        }
    } else if (flag) {
        _194.play("Enable");
    } else {
        _194.play("Disable");
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION complete__Q33scn12titlemenunew6OptionFv
void Option::complete() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 limit;
    u32 i;
    u32 base;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x7B74193F
    after1:
        mflr    r30
        lwz     r20, 0x0(r30)
        stw     r20, expected
    }
    selectPanel(static_cast<Kind>(_324), true);
    hash = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x50)
    after2:
        mflr    r18
        lwz     r23, 0x0(r18)
        add     r23, r23, r18
        stw     r23, start
        bl      after3
        opword  0x4969F609
        opword  MF_WORD(0x6C)
        opword  0x8430FC91
    after3:
        mflr    r18
        lwz     r22, 0x4(r18)
        add     r23, r23, r22
        stw     r23, end
    }
    _194.play("Enable");
    limit = end - start;
    base = start;
    i = -1;
    while (i != limit - 1) {
        i += 2;
        hash += *(u16*)(base + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash -= expected;
    hash += hash * 50;
    if (hash == 0) {
        mAnimSyncer->add(_194);
    } else {
        volatile u32 offset;
        volatile u32 addend;
        volatile u32 response;
        volatile u32 base2;

        asm {
            bl      after4
            opword  0x94946A80
            opword  MF_WORD(0x104)
        after4:
            mflr    r15
            lwz     r23, 0x4(r15)
            stw     r23, -0x4(r1)
            stw     r15, 0x0(r1)
            stw     r23, -0x4(r1)
            stw     r15, -0x8(r1)
            mtlr    r23
            bl      after5
            opword  MF_WORD(0x128)
            opword  MF_WORD(0x12C)
        after5:
            mflr    r30
            lwz     r20, 0x0(r30)
            lwz     r21, 0x4(r30)
            stw     r21, addend
            stw     r20, offset
            stw     r30, base2
        }
        offset = offset + 0x26;
        response = offset - addend;
        response = response + base2;
        asm {
            lwz     r26, response
            mtlr    r26
            blr
        }
    }
}
#undef MF_FUNCTION

void Option::unlockComplete() {
    mAnimSyncer->remove(_194);
    selectPanel(static_cast<Kind>(_324), false);
    mSequence.start();
}

#define MF_FUNCTION selectPanel__Q33scn12titlemenunew6OptionFQ43scn12titlemenunew6Option4Kindb
void Option::selectPanel(Kind kind, bool flag) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    hash = 0x811C9E29;
    asm {
        bl      after1
        opword  MF_WORD(0x3C)
        opword  0x0C16B390
        opword  0x0F0C3F02
        opword  MF_WORD(0x48)
        opword  0x8C984A81
    after1:
        mflr    r30
        lwz     r21, 0x0(r30)
        stw     r21, start
        lwz     r18, 0xc(r30)
        add     r21, r21, r18
        stw     r21, end
    }
    _194.pane("SoundN").hide();
    last = end;
    word = start;
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash ^= *(u16*)word;
        hash *= 0x010001AB;
    }
    _194.pane("TheaterN").hide();
    asm {
        bl      after2
        opword  MF_WORD(0xE4)
        opword  0x7C099B76
    after2:
        mflr    r16
        lwz     r26, 0x0(r16)
        stw     r26, expected
    }
    hash += hash << 13;
    _194.pane("OptionN").hide();
    hash ^= hash >> 7;
    hash += hash << 3;
    switch (kind) {
    case KIND_0:
        _194.pane("SoundN").show();
        _194.pane("SoundNormalN").setVisibility(!flag);
        _194.pane("SoundCompN").setVisibility(flag);
        _194.pane("SoundTitle").setText(app::Message::TextTitleMenu("ButtonSound"));
        _194.pane("Titlehadow").setText(app::Message::TextTitleMenu("ButtonSound"));
        _194.pane("SoundTitleComp").setText(app::Message::TextTitleMenu("ButtonSound"));
        _194.pane("ShadowText01").setText(app::Message::TextTitleMenu("ButtonSound"));
        break;
    case KIND_1:
        _194.pane("TheaterN").show();
        _194.pane("TheaterNormalN").setVisibility(!flag);
        _194.pane("TheaterCompN").setVisibility(flag);
        _194.pane("TheaterTitle").setText(app::Message::TextTitleMenu("ButtonTheater"));
        _194.pane("Titlehadow02").setText(app::Message::TextTitleMenu("ButtonTheater"));
        _194.pane("TheaterTitleComp").setText(app::Message::TextTitleMenu("ButtonTheater"));
        _194.pane("ShadowText03").setText(app::Message::TextTitleMenu("ButtonTheater"));
        break;
    case KIND_2:
        _194.pane("OptionN").show();
        _194.pane("OptionTitleN").setText(app::Message::TextTitleMenu("ButtonOption"));
        _194.pane("Titlehadow04").setText(app::Message::TextTitleMenu("ButtonOption"));
        break;
    }
    hash ^= hash >> 17;
    hash += hash << 5;
    if ((hash ^ expected) == 0) {
        _328 = flag;
    } else {
        volatile u32 response;
        volatile u32 addend;
        volatile u32 base2;
        volatile u32 offset;

        asm {
            bl      after3
            opword  0xC8D57F91
            opword  0x5C785281
            opword  0xECA96980
            opword  MF_WORD(0x48C)
        after3:
            mflr    r15
            lwz     r19, 0xc(r15)
            stw     r19, -0x4(r1)
            stw     r15, 0x0(r1)
            stw     r19, -0x4(r1)
            stw     r15, -0x8(r1)
            mtlr    r19
            bl      after4
            opword  MF_WORD(0x4B0)
            opword  MF_WORD(0x4B4)
        after4:
            mflr    r23
            lwz     r20, 0x0(r23)
            stw     r23, base2
            lwz     r24, 0x4(r23)
            stw     r20, offset
            stw     r24, addend
        }
        response = offset ^ addend;
        response = response + base2;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    }
}
#undef MF_FUNCTION

lyt::PaneAccessor Option::parent() {
    return mLayout.parent();
}

void Option::setParent(const lyt::PaneAccessor& parent) {
    mLayout.unsetParent();
    mLayout.setParent(parent);
}

#define MF_FUNCTION cursorParent__Q33scn12titlemenunew6OptionFv
lyt::PaneAccessor Option::cursorParent() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0xE6902E02
        opword  0x7884EE93
        opword  MF_WORD(0x2C)
        opword  0xB0742181
    after1:
        mflr    r19
        lwz     r23, 0x0(r19)
        lwz     r27, 0xc(r19)
        stw     r23, end
        stw     r27, start
        bl      after2
        opword  MF_WORD(0x4C)
        opword  0x1CB2B8E2
    after2:
        mflr    r17
        lwz     r20, 0x0(r17)
        stw     r20, expected
    }
    word = start;
    last = end;
    hash = 0xB3;
    for (;;) {
        if (word == last) {
            break;
        }
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
        word += 2;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    switch (_324) {
    case 0:
        if (hash - expected != 0 || _328) {
            return _194.pane("SoundCursorN");
        } else {
            return _194.rootPane();
        }
    case 1:
        if (hash - expected != 0 || _328) {
            return _194.pane("TheaterCursorN");
        } else {
            return _194.rootPane();
        }
    case 2:
        return _194.rootPane();
    default:
        while (hash - expected != 0) {
        }
        return lyt::PaneAccessor();
    }
}
#undef MF_FUNCTION

void Option::focus() {
    mLayout.play("Focus");
}

void Option::unfocus() {
    mLayout.play("UnFocus");
}

void Option::decide() {
    mAnimSyncer->remove(_194);
    mLayout.play("Wait");
    _194.play("Decide");
}

void Option::unlock() {
    mAnimSyncer->remove(_194);
    selectPanel(static_cast<Kind>(_324), false);
    _194.play("Unlock");
}

bool Option::isAnimEnd() const {
    return _194.isAnimEnd();
}

}}  // namespace scn::titlemenunew
