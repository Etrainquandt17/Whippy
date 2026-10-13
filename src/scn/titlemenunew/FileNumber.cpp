#include "scn/titlemenunew/FileNumber.h"

#include "app/Application.h"
#include "app/BackupFileAccessor.h"
#include "app/Message.h"
#include "app/SaveInfo.h"
#include "hel/debug/Print.h"
#include "lyt/LayoutContext.h"
#include "metafortress.h"

namespace scn {
namespace titlemenunew {

#define MF_FUNCTION __ct__Q33scn12titlemenunew10FileNumberFRQ23mem10IAllocatorRCQ23lyt12PaneAccessorRQ24info10AnimSyncer
FileNumber::FileNumber(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, info::AnimSyncer& animSyncer)
    : mLayout(lyt::LayoutContext("titlemenunew/Main", "KirbyIconPlate", allocator))
    , mIcon(allocator, mLayout.pane("KbIconN"))
    , mCompleteMark(allocator, mLayout.pane("CrownN"), animSyncer)
    , _4B4(0)
    , _4B8(false) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 base;
    u32 hash;
    u32 i;
    u32 size;

    asm {
        bl      after1
        opword  0xE4798A01
        opword  0xC8904690
        opword  MF_WORD(0xC8)
        opword  MF_WORD(0xCC)
        opword  0x4C074281
    after1:
        mflr    r26
        lwz     r19, 0x8(r26)
        lwz     r16, 0xc(r26)
        add     r16, r19, r16
        stw     r19, start
        stw     r16, end
    }
    base = start;
    size = end - base;
    mLayout.setParent(parent);
    asm {
        bl      after2
        opword  MF_WORD(0x108)
        opword  0xBAAFD815
    after2:
        mflr    r20
        lwz     r24, 0x0(r20)
        stw     r24, expected
    }
    hash = 0xB3;
    mLayout.pane("FileN").setText(app::Message::TextTitleMenu("File"));
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash = (hash << 4 ^ hash >> 28) ^ *(u16*)(base + i - 1);
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    mLayout.rootPane().setVisibility(false);
    base = hash << 3;
    hash += base;
    base = hash >> 17;
    hash ^= base;
    base = hash << 5;
    hash += base;
    base = expected;
    hash -= base;
    if (hash == 0) {
        update(0);
    } else {
        volatile u32 base2;
        volatile u32 response;
        volatile u32 addend;
        volatile u32 offset;

        asm {
            stw     r27, -0x4(r1)
            bl      after3
            opword  MF_WORD(0x1F4)
        after3:
            mflr    r27
            lwz     r24, 0x0(r27)
            stw     r24, 0x0(r1)
            stw     r27, 0x4(r1)
            mtlr    r24
            bl      after4
            opword  MF_WORD(0x210)
            opword  0x180C2181
            opword  MF_WORD(0x218)
        after4:
            mflr    r20
            lwz     r21, 0x0(r20)
            stw     r20, base2
            lwz     r15, 0x8(r20)
            stw     r21, offset
            stw     r15, addend
        }
        offset = offset + 0xFF;
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

FileNumber::~FileNumber() {
    if (_4B4 == 3) {
        app::BackupFileAccessor::Save(app::SAVE_INFO_LAYOUT_KIND_1);
    }
}

void FileNumber::updateFrame() {
    mLayout.updateFrame();
    mIcon.updateFrame();
    mCompleteMark.updateFrame();
    switch (_4B4) {
    case 1:
    case 2:
        if (mLayout.isAnimEnd()) {
            _4B4 = 0;
        }
        break;
    case 3:
        if (mLayout.isAnimEnd()) {
            app::BackupFileAccessor::Save(app::SAVE_INFO_LAYOUT_KIND_1);
            _4B4 = 4;
        }
        break;
    case 4:
        if (!hel::common::ExplicitSingleton<app::Application>::object_->saveInfo().isDisplayNow()) {
            _4B4 = 0;
            if (_4B8) {
                in();
            }
        }
        break;
    }
}

#define MF_FUNCTION update__Q33scn12titlemenunew10FileNumberFUl
void FileNumber::update(u32 file) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0x882C9E92
        opword  MF_WORD(0x28)
    after1:
        mflr    r29
        lwz     r18, 0x0(r29)
        add     r18, r18, r29
        lwz     r17, 0x8(r29)
        stw     r18, start
        add     r17, r17, r18
        stw     r17, end
    }
    mLayout.pane("FileNumber").setText(hel::debug::Print::HelSPrintfImpl("%d", file + 1));
    asm {
        bl      after2
        opword  MF_WORD(0x8C)
        opword  0xEABDDE09
    after2:
        mflr    r22
        lwz     r24, 0x0(r22)
        stw     r24, expected
    }
    hash = 0;
    word = start;
    last = end;
    mIcon.update(file);
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash *= 151;
        hash += *(u16*)word;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected == 0 && app::BackupFileAccessor(file).completed()) {
        mCompleteMark.show();
        mCompleteMark.select();
    } else {
        mCompleteMark.hide();
    }
}
#undef MF_FUNCTION

void FileNumber::in() {
    if (_4B4 == 0 || _4B4 == 2) {
        mLayout.rootPane().show();
        if (_4B4 == 2) {
            f32 frame = mLayout.frame();
            mLayout.play("In");
            mLayout.setFrame(mLayout.totalFrame() - frame);
        } else {
            mLayout.play("In");
        }
        _4B4 = 1;
    }
    _4B8 = true;
}

void FileNumber::out() {
    if (_4B4 == 0 || _4B4 == 1) {
        if (_4B4 == 1) {
            f32 frame = mLayout.frame();
            mLayout.play("Out");
            mLayout.setFrame(mLayout.totalFrame() - frame);
        } else {
            mLayout.play("Out");
        }
        _4B4 = 2;
    }
    _4B8 = false;
}

void FileNumber::save() {
    out();
    _4B8 = true;
    _4B4 = 3;
}

void FileNumber::show() {
    if (hel::common::ExplicitSingleton<app::Application>::object_->saveInfo().isDisplayNow()) {
        _4B4 = 4;
    } else {
        mLayout.rootPane().show();
        mLayout.play("Wait");
        _4B4 = 0;
    }
    _4B8 = true;
}

}}  // namespace scn::titlemenunew
