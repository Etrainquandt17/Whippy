#define MEM_EXPLICITAUTODELETEARRAY_INLINE

#include "pause/PageDropout.h"

#include "app/Application.h"
#include "app/Message.h"
#include "hel/common/ExplicitSingleton.h"
#include "hel/common/FixedStringIN.h"
#include "lyt/LayoutContext.h"
#include "metafortress.h"
#include "nand/NandManager.h"
#include "pause/Component.h"
#include "pause/Constant.h"
#include "pause/HID.h"
#include "pause/Result.h"
#include "pause/ResultSetter.h"
#include "snd/SoundSystem.h"
#include "snd/SystemSERequestor.h"
#include "std/tr1/reference_wrapper.h"
#include "util/ObjList.h"

namespace pause {

namespace {

struct EntryContext {
    const Result* mEntries;
    u32 mCount;
};

const Result T_ENTRIES_WORLDMAP[] = { RESULT_0, RESULT_3 };
const Result T_ENTRIES_LEVELMAP[] = { RESULT_0, RESULT_4, RESULT_3 };
const Result T_ENTRIES_SHIPMAP[] = { RESULT_0, RESULT_4, RESULT_3 };
const Result T_ENTRIES_STAGE[] = { RESULT_0, RESULT_2 };
const Result T_ENTRIES_CHALLENGE[] = { RESULT_0, RESULT_6, RESULT_7 };
const Result T_ENTRIES_THEARENA[] = { RESULT_0, RESULT_8 };
const Result T_ENTRIES_SUBGAME[] = { RESULT_0, RESULT_1 };

const EntryContext T_ENTRY_CONTEXTS[] = {
    { T_ENTRIES_WORLDMAP, 2 },  { T_ENTRIES_LEVELMAP, 3 },  { T_ENTRIES_SHIPMAP, 3 },  { T_ENTRIES_STAGE, 2 },
    { T_ENTRIES_STAGE, 2 },     { T_ENTRIES_CHALLENGE, 3 }, { T_ENTRIES_THEARENA, 2 }, { T_ENTRIES_SUBGAME, 2 },
};

// Indexed by Result.
const char* const T_LABELS[] = {
    "Continue",   "ExitStage", "ExitStage", "ReturnModeSelect", "ReturnWorldMap",
    "Again",      "Again",     "ExitStage", "BattleKing",
};

#define MF_FUNCTION tGetContext__Q25pause29_unnamed_PageDropout_prt_cpp_FQ25pause8ModeKind
EntryContext tGetContext(ModeKind mode) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 hash;
    u32 size;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xB8900D7F
    after1:
        mflr    r19
        lwz     r21, 0x0(r19)
        stw     r21, expected
    }
    hash = 0xC1;
    asm {
        bl      after2
        opword  MF_WORD(0x40)
        opword  0xE83B1480
        opword  0xBCEA4990
        opword  MF_WORD(0x4C)
        opword  0xEC36B490
        opword  0x6C93A691
    after2:
        mflr    r20
        lwz     r24, 0x0(r20)
        lwz     r19, 0xc(r20)
        stw     r24, start
        stw     r19, end
    }
    base = start;
    size = end - base;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash = (hash << 4 ^ hash >> 28) ^ *(u16*)(base + i - 1);
    }
    base = expected;
    hash = base ^ hash;
    base = hash >> 6;
    hash = hash - base;
    if (hash == 0) {
        return T_ENTRY_CONTEXTS[mode];
    }
    volatile u32 addend;
    volatile u32 response;
    volatile u32 base2;
    volatile u32 offset;

    asm {
        bl      after3
        opword  0x30D59380
        opword  MF_WORD(0xE4)
    after3:
        mflr    r19
        lwz     r29, 0x4(r19)
        stw     r29, -0x4(r1)
        stw     r19, 0x0(r1)
        stw     r29, -0x4(r1)
        stw     r19, -0x8(r1)
        mtlr    r29
        bl      after4
        opword  MF_WORD(0x108)
        opword  0x26C72100
        opword  MF_WORD(0x110)
    after4:
        mflr    r29
        lwz     r27, 0x0(r29)
        lwz     r26, 0x8(r29)
        stw     r26, addend
        stw     r27, offset
        stw     r29, base2
    }
    offset = offset + 0xD1;
    response = offset - addend;
    response = response + base2;
    asm {
        lwz     r30, response
        mtlr    r30
        blr
    }
}
#undef MF_FUNCTION

const char* tButtonPaneName(u32 count, u32 index) {
    switch (count) {
    case 2:
        switch (index) {
        case 0:
            return "ButtonA1N";
        case 1:
            return "ButtonA2N";
        }
        break;
    case 3:
        switch (index) {
        case 0:
            return "ButtonB1N";
        case 1:
            return "ButtonB2N";
        case 2:
            return "ButtonB3N";
        }
        break;
    }
    return "";
}

}

#define MF_FUNCTION __ct__Q25pause11PageDropoutFRQ25pause9Component
PageDropout::PageDropout(Component& component)
    : mComponent(component)
    , mLayout(lyt::LayoutContext(Constant::LytResPathPage(PAGE_RES_KIND_0), "DropoutWindow", component.allocator()))
    , mWindow(component, mLayout.paneByName("WindowN"), tGetContext(mComponent.contextInit().modeKind()).mCount == 3)
    , mConfirm(component.allocator(), mComponent.base().pane("ConfirmN"), L"", L"", L"", 0, true, false, "common/Main",
               "ConfirmWindow")
    , _BBC(0)
    , mSelected(0)
    , mButtons(component.allocator()) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  0x60068580
        opword  MF_WORD(0x160)
        opword  0x28ADBD80
        opword  0x7C745F80
        opword  MF_WORD(0x16C)
        opword  0xB8C4DD80
    after1:
        mflr    r15
        lwz     r28, 0x4(r15)
        stw     r28, start
        lwz     r21, 0x10(r15)
        add     r28, r28, r21
        stw     r28, end
    }
    mConfirm.changeButtonSizeSmall();
    hash = 0;
    limit = end - start + 1;
    i = 1;
    base = start;
    for (; i != limit; i += 2) {
        hash *= 61;
        hash += *(u16*)(base + i - 1);
    }
    asm {
        bl      after2
        opword  MF_WORD(0x1D4)
        opword  0x6E1C7086
    after2:
        mflr    r14
        lwz     r27, 0x0(r14)
        stw     r27, expected
    }
    mConfirm.freezeOnYes(expected == hash);
    mConfirm.cancelFgm(0x175);
    mConfirm.defaultButton(1);
    EntryContext context = tGetContext(mComponent.contextInit().modeKind());
    for (u32 n = 0; n < context.mCount; n++) {
        // A reference to a temporary: as a named local the value takes a register that moves this and component.
        const u32& entry = context.mEntries[n];
        mButtons.add(std::tr1::ref(mComponent), "Button", mLayout.paneByName(tButtonPaneName(context.mCount, n)),
                     app::Message::TextPause(hel::common::FixedStringIN<char, 32>::FromFormat("Dropout%s", T_LABELS[entry])),
                     true);
    }
    mButtons[mSelected].setSelected();
}
#undef MF_FUNCTION

const wchar_t* PageDropout::pageFrameTitle() const {
    return app::Message::TextPause("PageTitleDropout");
}

lyt::Layout& PageDropout::pageMainLayout() {
    return mLayout;
}

void PageDropout::pageProcAnim() {
    mLayout.updateFrame();
    mConfirm.updateFrame();
    for (u32 i = 0; i < mButtons.count(); i++) {
        mButtons[i].updateFrame();
    }
}

void PageDropout::pageProcHID() {
    switch (_BBC) {
    case 0:
        procHIDItemSelect();
        break;
    case 1:
        procHIDItemDecide();
        break;
    case 2:
        procHIDConfirm();
        break;
    }
}

bool PageDropout::pageIsBusy() const {
    return _BBC != 0;
}

#define MF_FUNCTION procHIDItemSelect__Q25pause11PageDropoutFv
void PageDropout::procHIDItemSelect() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  0x006F9F02
        opword  MF_WORD(0x2C)
        opword  0xDA3F190A
        opword  0x580B7092
        opword  MF_WORD(0x38)
        opword  0x8EDBC209
        opword  0x60086480
    after1:
        mflr    r17
        lwz     r14, 0x10(r17)
        stw     r14, start
        lwz     r26, 0x4(r17)
        stw     r26, end
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    for (; i != limit; i += 2) {
        hash += *(u16*)(base + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xA0)
        opword  0x62E76004
    after2:
        mflr    r19
        lwz     r28, 0x0(r19)
        stw     r28, expected
    }
    limit = expected;
    hash = limit ^ hash;
    limit = hash << 4;
    hash = hash | limit;
    if (hash == 0) {
        if (mComponent.resultSetter().wasSet()) {
            return;
        }
        if (mComponent.hid().btn().isTrigger(0x100)) {
            if (mButtons[mSelected].isEnable()) {
                mButtons[mSelected].decide();
                _BBC = 1;
                EntryContext context = tGetContext(mComponent.contextInit().modeKind());
                switch (context.mEntries[mSelected]) {
                case RESULT_0:
                    mComponent.seReq().start(0x82);
                    _BBC = 1;
                    break;
                case RESULT_4:
                    mComponent.seReq().start(0x173);
                    snd::stopAllSoundForPauseMenuDropoutScene();
                    break;
                default:
                    mComponent.seReq().start(0x91);
                    break;
                }
            } else {
                mComponent.seReq().start(0x146);
            }
        } else {
            u32 index = mSelected;
            if (mComponent.hid().btn().isTrigger(2)) {
                if (index == 0) {
                    index = mButtons.count();
                }
                index--;
            } else if (mComponent.hid().btn().isTrigger(1)) {
                index++;
                if (index == mButtons.count()) {
                    index = 0;
                }
            }
            if (index != mSelected) {
                mButtons[mSelected].setNotSelected();
                mButtons[index].setSelected();
                mSelected = index;
                mComponent.seReq().start(0x80);
            }
        }
    } else {
        volatile u32 addend;
        volatile u32 offset;
        volatile u32 base2;
        volatile u32 response;

        asm {
            bl      after3
            opword  0x24C16680
            opword  MF_WORD(0x298)
        after3:
            mflr    r14
            lwz     r26, 0x4(r14)
            stw     r26, -0x4(r1)
            stw     r14, 0x0(r1)
            stw     r26, -0x4(r1)
            stw     r14, -0x8(r1)
            mtlr    r26
            bl      after4
            opword  MF_WORD(0x2BC)
            opword  0xC1DEAB03
            opword  MF_WORD(0x2C4)
        after4:
            mflr    r23
            lwz     r16, 0x0(r23)
            lwz     r24, 0x8(r23)
            stw     r24, addend
            stw     r16, offset
            stw     r23, base2
        }
        offset = offset + 0xA2;
        response = offset + addend;
        response = response + base2;
        asm {
            lwz     r30, response
            mtlr    r30
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION procHIDItemDecide__Q25pause11PageDropoutFv
void PageDropout::procHIDItemDecide() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;
    u32 t;

    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x864C5C04
        opword  MF_WORD(0x34)
    after1:
        mflr    r26
        lwz     r29, 0x0(r26)
        add     r29, r29, r26
        stw     r29, start
        lwz     r27, 0x8(r26)
        add     r29, r29, r27
        stw     r29, end
    }
    t = 0x811D0000;
    hash = t - 0x61D7;
    limit = end - start + 1;
    i = 1;
    base = start;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001AB;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xA0)
        opword  0x39BCF2EF
    after2:
        mflr    r24
        lwz     r17, 0x0(r24)
        stw     r17, expected
    }
    limit = expected;
    hash ^= limit;
    if (hash != 0) {
        volatile u32 base2;
        volatile u32 offset;
        volatile u32 addend;
        volatile u32 response;

        asm {
            bl      after3
            opword  0xD0AF4A0C
            opword  0x50E14E92
            opword  0x6CE94093
            opword  MF_WORD(0xD4)
        after3:
            mflr    r30
            lwz     r28, 0xc(r30)
            stw     r28, -0x4(r1)
            stw     r30, 0x0(r1)
            stw     r28, -0x4(r1)
            stw     r30, -0x8(r1)
            mtlr    r28
            bl      after4
            opword  MF_WORD(0xF8)
            opword  0xFC137F81
            opword  0x0CA41A93
            opword  MF_WORD(0x104)
        after4:
            mflr    r30
            lwz     r15, 0x0(r30)
            stw     r30, base2
            lwz     r27, 0xc(r30)
            stw     r15, offset
            stw     r27, addend
        }
        offset = offset ^ 0x5D;
        response = offset - addend;
        response = response + base2;
        asm {
            lwz     r23, response
            mtlr    r23
            blr
        }
    } else if (mButtons[mSelected].isDecideAnimEnd()) {
        EntryContext context = tGetContext(mComponent.contextInit().modeKind());
        Result result = context.mEntries[mSelected];
        switch (result) {
        case RESULT_0:
        case RESULT_4:
            mComponent.resultSetter().set(result);
            break;
        default: {
            const char* label;
            switch (result) {
            case RESULT_6:
                label = "DropoutAgain2";
                break;
            case RESULT_3:
                label = "DropoutReturnModeSelect2";
                break;
            case RESULT_8:
                label = "DropoutBattleKing2";
                break;
            default:
                if (hel::common::ExplicitSingleton<app::Application>::object_->nandManager().isDisable()) {
                    label = "ConfirmNotSaved2";
                } else {
                    label = "ConfirmNotSaved";
                }
                break;
            }
            mConfirm.setText(app::Message::TextPause(label));
            mConfirm.setText0(app::Message::TextPause(hel::common::FixedStringIN<char, 32>::FromFormat("%s_Yes", label)));
            mConfirm.setText1(app::Message::TextPause(hel::common::FixedStringIN<char, 32>::FromFormat("%s_No", label)));
            mConfirm.open(mComponent.hid().padChan());
            _BBC = 2;
            break;
        }
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION procHIDConfirm__Q25pause11PageDropoutFv
void PageDropout::procHIDConfirm() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 base;
    u32 limit;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x8C8D9B91
        opword  0x880E3280
    after1:
        mflr    r26
        lwz     r24, 0x0(r26)
        add     r24, r24, r26
        stw     r24, start
        bl      after2
        opword  0x8C3A4780
        opword  MF_WORD(0x4C)
        opword  0xB8FDCC80
    after2:
        mflr    r26
        lwz     r16, 0x4(r26)
        add     r24, r24, r16
        stw     r24, end
    }
    i = 1;
    base = start;
    limit = end - base + 1;
    asm {
        bl      after3
        opword  MF_WORD(0x7C)
        opword  0x3049803F
    after3:
        mflr    r29
        lwz     r25, 0x0(r29)
        stw     r25, expected
    }
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 37;
        hash += *(u16*)(base + i - 1);
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash != expected) {
        volatile u32 base2;
        volatile u32 response;
        volatile u32 addend;
        volatile u32 offset;

        asm {
            stw     r17, -0x4(r1)
            bl      after4
            opword  MF_WORD(0xD4)
        after4:
            mflr    r17
            lwz     r16, 0x0(r17)
            stw     r16, 0x0(r1)
            stw     r17, 0x4(r1)
            mtlr    r16
            bl      after5
            opword  MF_WORD(0xF0)
            opword  0xB8298780
            opword  MF_WORD(0xF8)
        after5:
            mflr    r23
            lwz     r18, 0x0(r23)
            stw     r23, base2
            lwz     r14, 0x8(r23)
            stw     r18, offset
            stw     r14, addend
        }
        offset = offset + 0xAF;
        response = offset + addend;
        response = response + base2;
        asm {
            lwz     r21, response
            mtlr    r21
            blr
        }
    } else if (mComponent.isReqClose() && !mConfirm.isClosed()) {
        mConfirm.forceClose();
        _BBC = 0;
    } else if (mConfirm.isClosed()) {
        switch (mConfirm.result()) {
        case 1:
        case 3:
            _BBC = 0;
            break;
        case 0: {
            EntryContext context = tGetContext(mComponent.contextInit().modeKind());
            mComponent.resultSetter().set(context.mEntries[mSelected]);
            snd::stopAllSoundForPauseMenuDropoutScene();
            break;
        }
        case 2:
            break;
        }
    }
}
#undef MF_FUNCTION

PageDropout::~PageDropout() {}

}
