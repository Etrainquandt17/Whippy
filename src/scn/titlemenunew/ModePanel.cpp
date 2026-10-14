#define MEM_EXPLICITAUTODELETEARRAY_INLINE

#include "scn/titlemenunew/ModePanel.h"

#include "app/Application.h"
#include "app/BackupFileAccessor.h"
#include "hel/common/ExplicitSingleton.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "lyt/LayoutContext.h"
#include "metafortress.h"
#include "std/tr1/reference_wrapper.h"
#include "storage/StorageManager.h"
#include "storage/VolatileData.h"
#include "util/ObjList.h"

using app::Application;
using app::BackupFileAccessor;
using hel::common::ExplicitSingleton;
using hel::math::Matrix34;
using hel::math::Vector2;
using std::tr1::ref;

namespace {

#define MF_FUNCTION showAsEnable__27_unnamed_ModePanel_prt_cpp_FQ27storage11UnlockState
bool showAsEnable(storage::UnlockState state) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x78FB9891
        opword  0x4D16F30A
        opword  MF_WORD(0x34)
        opword  0x9400DB91
        opword  0x90162480
    after1:
        mflr    r17
        lwz     r27, 0xc(r17)
        lwz     r15, 0x0(r17)
        add     r15, r15, r17
        stw     r15, start
        add     r27, r27, r15
        stw     r27, end
        bl      after2
        opword  MF_WORD(0x60)
        opword  0x39FD1F12
    after2:
        mflr    r20
        lwz     r25, 0x0(r20)
        stw     r25, expected
    }
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
    hash = (expected & ~hash) | (hash & ~expected);
    hash -= hash >> 2;
    if (hash == 0) {
        return state == storage::UNLOCK_STATE_2 || state == storage::UNLOCK_STATE_3;
    }
    volatile u32 base2;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 addend;

    asm {
        bl      after3
        opword  0xD6326107
        opword  0x54916590
        opword  0x1690FA00
        opword  MF_WORD(0xF4)
    after3:
        mflr    r14
        lwz     r28, 0xc(r14)
        stw     r28, -0x4(r1)
        stw     r14, 0x0(r1)
        stw     r28, -0x4(r1)
        stw     r14, -0x8(r1)
        mtlr    r28
        bl      after4
        opword  MF_WORD(0x118)
        opword  0x242F1892
        opword  MF_WORD(0x120)
    after4:
        mflr    r27
        lwz     r28, 0x8(r27)
        stw     r28, addend
        lwz     r28, 0x0(r27)
        stw     r27, base2
        stw     r28, offset
    }
    addend = 0;
    response = offset;
    response = response + base2;
    asm {
        lwz     r27, response
        mtlr    r27
        blr
    }
}
#undef MF_FUNCTION

}

namespace scn {
namespace titlemenunew {

#define MF_FUNCTION __ct__Q33scn12titlemenunew9ModePanelFRQ23mem10IAllocatorRCQ23lyt12PaneAccessorRCQ23lyt12PaneAccessorRQ24info10AnimSyncer
ModePanel::ModePanel(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, const lyt::PaneAccessor& pane,
                     info::AnimSyncer& animSyncer)
    : mLayout(lyt::LayoutContext("titlemenunew/Main", "ModeSelectBase", allocator))
    , mFileNumber(allocator, mLayout.pane("KirbyIconPlateN"), animSyncer)
    , mFiles(allocator)
    , mSubGames(allocator)
    , mArenas(allocator)
    , mOptions(allocator)
    , mHelp(allocator, mLayout.pane("Help01N"))
    , mSE()
    , _8A0(pane)
    , _8B4(0)
    , _8B8() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 base;
    u32 hash;
    u32 i;

    mLayout.setParent(parent);
    asm {
        bl      after1
        opword  MF_WORD(0x150)
        opword  0x31F47E15
    after1:
        mflr    r20
        lwz     r21, 0x0(r20)
        stw     r21, expected
    }
    hash = 0xC5;
    mLayout.rootPane().setVisibility(false);
    asm {
        bl      after2
        opword  0x4CE3E880
        opword  MF_WORD(0x194)
        opword  0xB46F1080
        opword  MF_WORD(0x19C)
        opword  0x68C9A605
        opword  0xABAADD0A
    after2:
        mflr    r19
        lwz     r26, 0xc(r19)
        stw     r26, start
        lwz     r22, 0x4(r19)
        stw     r22, end
    }
    // Bound to a reference so that it is a compiler temporary. As a named local it
    // lands in another saved register, in every order of the declarations.
    const u32& size = end - start;
    base = start;
    mFiles.add(ref(allocator), mLayout.pane("NormalOnlyN"), true, FileStatus::KIND_0, 0, ref(animSyncer));
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(base + i - 1);
    }
    hash += hash << 3;
    mFiles.add(ref(allocator), mLayout.pane("NormalN"), true, FileStatus::KIND_1, 0, ref(animSyncer));
    hash ^= hash >> 11;
    hash += hash << 15;
    mFiles.add(ref(allocator), mLayout.pane("ExtraN"), hash - expected != 0, FileStatus::KIND_2, 0, ref(animSyncer));
    mSubGames.add(ref(allocator), mLayout.pane("BungyN"), SubGame::KIND_0);
    mSubGames.add(ref(allocator), mLayout.pane("GunN"), SubGame::KIND_1);
    mArenas.add(ref(allocator), mLayout.pane("KakutouN0"), TheArena::KIND_0, ref(animSyncer));
    mArenas.add(ref(allocator), mLayout.pane("KakutouN1"), TheArena::KIND_1, ref(animSyncer));
    mArenas.add(ref(allocator), mLayout.pane("ShinKakutouN"), TheArena::KIND_2, ref(animSyncer));
    mOptions.add(ref(allocator), mLayout.pane("SoundN"), Option::KIND_0, ref(animSyncer));
    mOptions.add(ref(allocator), mLayout.pane("TheaterN"), Option::KIND_1, ref(animSyncer));
    mOptions.add(ref(allocator), mLayout.pane("OptionN"), Option::KIND_2, ref(animSyncer));
}
#undef MF_FUNCTION

void ModePanel::updateFrame() {
    mLayout.updateFrame();
    mFileNumber.updateFrame();
    for (u32 i = 0; i < mFiles.count(); i++) {
        mFiles[i].updateFrame();
    }
    for (u32 i = 0; i < mSubGames.count(); i++) {
        mSubGames[i].updateFrame();
    }
    for (u32 i = 0; i < mArenas.count(); i++) {
        mArenas[i].updateFrame();
    }
    for (u32 i = 0; i < mOptions.count(); i++) {
        mOptions[i].updateFrame();
    }
    mHelp.updateFrame();
}

void ModePanel::show(u32 file) {
    mLayout.rootPane().show();
    if (BackupFileAccessor(file).theArenaExtraOpened()) {
        mLayout.play("SinKakutouOpen");
    } else {
        mLayout.play("Open");
    }
    mLayout.setFrameToTail();
    mLayout.reflectFrameToAnim();
    mFileNumber.show();
}

void ModePanel::appear(u32 file) {
    mLayout.rootPane().show();
    if (BackupFileAccessor(file).theArenaExtraOpened()) {
        mLayout.play("SinKakutouOpen");
    } else {
        mLayout.play("Open");
    }
    mFileNumber.in();
}

void ModePanel::disappear(u32 file) {
    restoreFrontButton();
    if (BackupFileAccessor(file).theArenaExtraOpened()) {
        mLayout.play("SinKakutouClose");
    } else {
        mLayout.play("Close");
    }
    mFileNumber.out();
}

#define MF_FUNCTION isAnimEnd__Q33scn12titlemenunew9ModePanelCFv
bool ModePanel::isAnimEnd() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 base;
    u32 i;
    u32 limit;
    u32 hash;
    u32 last;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xBB7A0206
        opword  MF_WORD(0x2C)
        opword  0x5074E691
        opword  0xC7DFC606
    after1:
        mflr    r29
        lwz     r27, 0x8(r29)
        stw     r27, start
        lwz     r16, 0x0(r29)
        stw     r16, end
    }
    hash = 0;
    limit = start;
    last = end;
    last = last - limit;
    limit = last + 1;
    last = end;
    asm {
        bl      after2
        opword  MF_WORD(0x68)
        opword  0xD15C0A44
    after2:
        mflr    r26
        lwz     r17, 0x0(r26)
        stw     r17, expected
    }
    i = -1;
    base = last - 1;
    for (;;) {
        i += 2;
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
    }
    limit = hash >> 10;
    hash ^= limit;
    limit = hash << 20;
    hash ^= limit;
    limit = expected;
    hash = hash - limit;
    if (hash != 0) {
        volatile u32 response;
        volatile u32 base2;
        volatile u32 addend;
        volatile u32 offset;

        asm {
            bl      after3
            opword  0xD8A06581
            opword  0x0C920B81
            opword  MF_WORD(0xDC)
        after3:
            mflr    r23
            lwz     r20, 0x8(r23)
            stw     r20, -0x4(r1)
            stw     r23, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r23, -0x8(r1)
            mtlr    r20
            bl      after4
            opword  MF_WORD(0x100)
            opword  0x5977A702
            opword  0x3C9CF091
            opword  MF_WORD(0x10C)
        after4:
            mflr    r24
            lwz     r19, 0x0(r24)
            lwz     r26, 0xc(r24)
            stw     r26, addend
            stw     r19, offset
            stw     r24, base2
        }
        offset = offset - 0x37;
        response = offset ^ addend;
        response = response + base2;
        asm {
            lwz     r24, response
            mtlr    r24
            blr
        }
    } else {
        return mLayout.isAnimEnd();
    }
}
#undef MF_FUNCTION

void ModePanel::focus(ModeKind kind) {
    modeButton(kind)->focus();
}

#define MF_FUNCTION unfocus__Q33scn12titlemenunew9ModePanelFQ33scn12titlemenunew8ModeKind
void ModePanel::unfocus(ModeKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  0xDF241B0D
        opword  0xB4199F93
        opword  MF_WORD(0x30)
        opword  MF_WORD(0x34)
        opword  0x40334292
        opword  0xD0076380
    after1:
        mflr    r23
        lwz     r30, 0x8(r23)
        lwz     r22, 0xc(r23)
        add     r22, r30, r22
        stw     r30, start
        stw     r22, end
    }
    last = end;
    word = start;
    hash = 0x811C9E07;
    for (; word != last; word += 2) {
        hash ^= *(u16*)word;
        hash *= 0x010001A7;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x90)
        opword  0x31C8FB66
    after2:
        mflr    r15
        lwz     r23, 0x0(r15)
        stw     r23, expected
    }
    hash -= expected;
    if (hash != 0) {
        volatile u32 addend;
        volatile u32 offset;
        volatile u32 response;
        volatile u32 base2;

        asm {
            bl      after3
            opword  0x1FF49904
            opword  0x3479E780
            opword  MF_WORD(0xC0)
        after3:
            mflr    r26
            lwz     r18, 0x8(r26)
            stw     r18, -0x4(r1)
            stw     r26, 0x0(r1)
            stw     r18, -0x4(r1)
            stw     r26, -0x8(r1)
            mtlr    r18
            bl      after4
            opword  MF_WORD(0xE4)
            opword  MF_WORD(0xE8)
        after4:
            mflr    r15
            stw     r15, base2
            lwz     r28, 0x0(r15)
            stw     r28, offset
            lwz     r17, 0x4(r15)
            stw     r17, addend
        }
        response = offset ^ addend;
        response = response + base2;
        asm {
            lwz     r28, response
            mtlr    r28
            blr
        }
    } else {
        modeButton(kind)->unfocus();
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION decide__Q33scn12titlemenunew9ModePanelFQ33scn12titlemenunew8ModeKind
void ModePanel::decide(ModeKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 hash;
    u32 last;
    u32 limit;

    hash = 0x811C9E53;
    asm {
        bl      after1
        opword  0xFF962D0E
        opword  0xB075D380
        opword  MF_WORD(0x38)
        opword  0x2C24BE92
        opword  MF_WORD(0x40)
        opword  0xE4926593
        opword  0x20D9DC93
    after1:
        mflr    r30
        lwz     r25, 0x8(r30)
        stw     r25, start
        lwz     r21, 0x10(r30)
        add     r25, r25, r21
        stw     r25, end
    }
    i = 1;
    last = end;
    limit = last - start + 1;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001D1;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xA8)
        opword  0x73629B0C
    after2:
        mflr    r20
        lwz     r22, 0x0(r20)
        stw     r22, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected != 0) {
        volatile u32 offset;
        volatile u32 base2;
        volatile u32 addend;
        volatile u32 response;

        asm {
            bl      after3
            opword  MF_WORD(0xE0)
            opword  0xE4A9CB0E
        after3:
            mflr    r21
            addi    r29, r21, 0x14
            mtlr    r29
            lwz     r19, 0x0(r21)
            stw     r19, -0x4(r1)
            stw     r29, 0x0(r1)
            stw     r21, 0x4(r1)
            blrl
            bl      after4
            opword  MF_WORD(0x10C)
            opword  MF_WORD(0x110)
        after4:
            mflr    r23
            lwz     r26, 0x4(r23)
            stw     r26, addend
            lwz     r26, 0x0(r23)
            stw     r23, base2
            stw     r26, offset
        }
        offset = offset - 0x2F;
        addend = 0;
        response = offset;
        response = response + base2;
        asm {
            lwz     r26, response
            mtlr    r26
            blr
        }
    } else {
        modeButton(kind)->decide();
    }
}
#undef MF_FUNCTION

void ModePanel::startUnlock(UnlockKind kind) {
    mSE.start(0x7E);
    bringToFront(*modeButton(kind));
    if (kind == UNLOCK_KIND_6) {
        mOptions[0].unlockComplete();
    } else if (kind == UNLOCK_KIND_8) {
        mOptions[1].unlockComplete();
    } else {
        modeButton(kind)->unlock();
    }
}

bool ModePanel::isUnlockAnimEnd(UnlockKind kind) const {
    return const_cast<ModePanel*>(this)->modeButton(kind)->isAnimEnd();
}

#define MF_FUNCTION cursorParent__Q33scn12titlemenunew9ModePanelFQ33scn12titlemenunew8ModeKind
lyt::PaneAccessor ModePanel::cursorParent(ModeKind kind) {
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
        opword  0x2DFCA9CE
    after1:
        mflr    r29
        lwz     r27, 0x0(r29)
        stw     r27, expected
    }
    t = 0x811D0000;
    hash = t - 0x623B;
    asm {
        bl      after2
        opword  MF_WORD(0x4C)
        opword  0xF0A6DF00
        opword  0x1023BD90
    after2:
        mflr    r14
        lwz     r29, 0x0(r14)
        stw     r29, start
        bl      after3
        opword  MF_WORD(0x68)
        opword  0x807F2890
        opword  0xECAC8580
    after3:
        mflr    r14
        lwz     r29, 0x0(r14)
        stw     r29, end
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000181;
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
    if (hash == 0) {
        return modeButton(kind)->cursorParent();
    } else {
        volatile u32 offset;
        volatile u32 response;
        volatile u32 addend;
        volatile u32 base2;

        asm {
            bl      after4
            opword  0x78504690
            opword  0x48BF6D91
            opword  MF_WORD(0x11C)
        after4:
            mflr    r26
            lwz     r20, 0x8(r26)
            stw     r20, -0x4(r1)
            stw     r26, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r26, -0x8(r1)
            mtlr    r20
            bl      after5
            opword  MF_WORD(0x140)
            opword  0xC810690F
            opword  0x68E10281
            opword  MF_WORD(0x14C)
        after5:
            mflr    r30
            lwz     r16, 0xc(r30)
            stw     r16, addend
            lwz     r16, 0x0(r30)
            stw     r30, base2
            stw     r16, offset
        }
        offset = offset - 0x9C;
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

#define MF_FUNCTION updateItemStatus__Q33scn12titlemenunew9ModePanelFv
void ModePanel::updateItemStatus() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 limit;
    u32 last;
    u32 hash;

    hash = 0x811C9E29;
    BackupFileAccessor accessor;
    asm {
        bl      after1
        opword  MF_WORD(0x34)
        opword  0xE196A051
    after1:
        mflr    r17
        lwz     r19, 0x0(r17)
        stw     r19, expected
    }
    u32 file = ExplicitSingleton<Application>::object_->storageManager().volatileData()._0[2];
    mFileNumber.update(file);
    asm {
        bl      after2
        opword  0xC83A1381
        opword  MF_WORD(0x6C)
        opword  0xCCC4DC91
        opword  MF_WORD(0x74)
    after2:
        mflr    r30
        lwz     r18, 0xc(r30)
        lwz     r27, 0x4(r30)
        stw     r27, end
        stw     r18, start
    }
    if (accessor.extraModeOpened()) {
        mFiles[0].hide();
        mFiles[1].show();
        mFiles[2].show();
        mFiles[1].updateStatus(file);
        mFiles[2].updateStatus(file);
    } else {
        mFiles[0].show();
        mFiles[1].hide();
        mFiles[2].hide();
        mFiles[0].updateStatus(file);
    }
    for (u32 n = 0; n < 2; n++) {
        mSubGames[n].enable(showAsEnable(accessor.subGameState(static_cast<storage::SubGameKind>(n))));
    }
    limit = end - start;
    last = end;
    if (accessor.theArenaOpened() && accessor.theArenaExtraOpened()) {
        mArenas[0].hide();
        mArenas[1].show();
        mArenas[2].show();
        mArenas[1].enable(true);
        mArenas[1].updateClearMark();
        mArenas[2].enable(showAsEnable(accessor.theArenaExtraState()));
        mArenas[2].updateClearMark();
    } else {
        mArenas[0].show();
        mArenas[1].hide();
        mArenas[2].hide();
        mArenas[0].enable(showAsEnable(accessor.theArenaState()));
        mArenas[0].updateClearMark();
    }
    i = -1;
    while (i != limit - 1) {
        i += 2;
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001AB;
    }
    if (showAsEnable(accessor.soundRoomCompleteState())) {
        mOptions[0].complete();
    } else {
        mOptions[0].enable(showAsEnable(accessor.soundRoomState()));
    }
    hash += hash << 3;
    if (showAsEnable(accessor.theaterRoomCompleteState())) {
        mOptions[1].complete();
    } else {
        mOptions[1].enable(showAsEnable(accessor.theaterRoomState()));
    }
    hash ^= hash >> 11;
    bool notBlank = !accessor.isBlank();
    hash += hash << 15;
    mOptions[2].enable(notBlank);
    last = expected;
    limit = last & ~hash;
    last = expected;
    last = hash & ~last;
    hash = limit | last;
    last = hash >> 7;
    hash = hash - last;
    if (hash == 0) {
        if (accessor.extraModeOpened()) {
            static_cast<IModeButton&>(mHelp).setParent(mLayout.pane("Help02N"));
        } else {
            static_cast<IModeButton&>(mHelp).setParent(mLayout.pane("Help01N"));
        }
    } else {
        volatile u32 base2;
        volatile u32 response;
        volatile u32 offset;
        volatile u32 addend;

        asm {
            stw     r22, -0x4(r1)
            bl      after3
            opword  MF_WORD(0x448)
            opword  0x08656980
            opword  0xF4A5D60B
        after3:
            mflr    r22
            lwz     r16, 0x0(r22)
            stw     r16, 0x0(r1)
            stw     r22, 0x4(r1)
            mtlr    r16
            bl      after4
            opword  MF_WORD(0x46C)
            opword  MF_WORD(0x470)
        after4:
            mflr    r19
            stw     r19, base2
            lwz     r20, 0x0(r19)
            stw     r20, offset
            lwz     r21, 0x4(r19)
            stw     r21, addend
        }
        offset = offset - 0xE;
        response = offset + addend;
        response = response + base2;
        asm {
            lwz     r24, response
            mtlr    r24
            blr
        }
    }
}
#undef MF_FUNCTION

void ModePanel::restoreFrontButton() {
    if (_8B4 != 0) {
        _8B4->setParent(_8B8);
        _8B4 = 0;
    }
}

IModeButton* ModePanel::modeButton(UnlockKind kind) {
    switch (kind) {
    case UNLOCK_KIND_0:
        return &mFiles[2];
    case UNLOCK_KIND_1:
        return &mSubGames[0];
    case UNLOCK_KIND_2:
        return &mSubGames[1];
    case UNLOCK_KIND_3:
        return &mArenas[0];
    case UNLOCK_KIND_4:
        return &mArenas[2];
    case UNLOCK_KIND_5:
    case UNLOCK_KIND_6:
        return &mOptions[0];
    case UNLOCK_KIND_7:
    case UNLOCK_KIND_8:
        return &mOptions[1];
    }
    return 0;
}

IModeButton* ModePanel::modeButton(ModeKind kind) {
    BackupFileAccessor accessor;
    switch (kind) {
    case MODE_KIND_0:
        if (accessor.extraModeOpened()) {
            return &mFiles[1];
        }
        return &mFiles[0];
    case MODE_KIND_1:
        return &mFiles[2];
    case MODE_KIND_2:
        return &mSubGames[0];
    case MODE_KIND_3:
        return &mSubGames[1];
    case MODE_KIND_4:
        if (accessor.theArenaExtraOpened()) {
            return &mArenas[1];
        }
        return &mArenas[0];
    case MODE_KIND_5:
        return &mArenas[2];
    case MODE_KIND_6:
        return &mOptions[0];
    case MODE_KIND_7:
        return &mOptions[1];
    case MODE_KIND_8:
        return &mOptions[2];
    case MODE_KIND_9:
        return &mHelp;
    }
    return 0;
}

void ModePanel::bringToFront(IModeButton& button) {
    if (_8B4 != 0) {
        _8B4->setParent(_8B8);
    }
    _8B4 = &button;
    _8B8 = button.parent();
    button.setParent(_8A0);
    _8A0.setTrans(_8B8.pos());
    Matrix34 mtx = _8B8.globalMtx();
    _8A0.setScale(Vector2(mtx.m[0][0], mtx.m[1][1]));
}

}}  // namespace scn::titlemenunew
