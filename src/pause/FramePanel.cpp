#define MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE

#include "pause/FramePanel.h"

#include "hel/common/FixedStringIN.h"
#include "lyt/LayoutContext.h"
#include "metafortress.h"
#include "pause/Component.h"
#include "pause/Constant.h"
#include "pause/ManualData.h"
#include "util/ObjList.h"

namespace pause {

namespace {

const char* const T_MOVE_NODE = "IconN";
const char* const T_FIX_NODE = "IconFixN";

}

#define MF_FUNCTION __ct__Q25pause10FramePanelFRQ25pause9Component
FramePanel::FramePanel(Component& component)
    : mComponent(component)
    , mFrame(lyt::LayoutContext(Constant::LytResPathMain(), "PauseFrame", component.allocator()))
    , mIcon(lyt::LayoutContext(Constant::LytResPathMain(), "Icon", mComponent.allocator()))
    , mAbilityIcon(mComponent.allocator())
    , _32C(0)
    , _330(FRAME_ICON_KIND_DROPOUT) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 last;
    u32 i;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0xA0)
        opword  0x4EB55004
        opword  MF_WORD(0xA8)
    after1:
        mflr    r19
        lwz     r20, 0x0(r19)
        add     r20, r20, r19
        lwz     r29, 0x8(r19)
        stw     r20, start
        add     r29, r29, r20
        stw     r29, end
    }
    hash = 0x811C9E29;
    mFrame.setParent(mComponent.base().paneByName("FrameN"));
    limit = end - start + 1;
    i = 1;
    last = end - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x010001AB;
        i += 2;
    }
    mIcon.setParent(mFrame.paneByName(T_MOVE_NODE));
    hash += hash << 13;
    asm {
        bl      after2
        opword  MF_WORD(0x178)
        opword  0xB2759FBF
    after2:
        mflr    r16
        lwz     r30, 0x0(r16)
        stw     r30, expected
    }
    hash ^= hash >> 7;
    mFrame.setAnimByName("Wait");
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    mFrame.start(expected == hash);
}
#undef MF_FUNCTION

void FramePanel::reset() {
    mAbilityIcon.destruct();
}

void FramePanel::setup() {
    ManualKind kind = mComponent.contextOpen().manualKind();
    if (kind != MANUAL_KIND_35) {
        mAbilityIcon.construct(
            lyt::LayoutContext(ManualData::PathFrameAbilityIcon(kind), "AbStar", mComponent.allocator()));
        mAbilityIcon->setParent(mIcon.paneByName("AbIconN"));
        mAbilityIcon->rootPane().hide();
    }
}

void FramePanel::setTotalPageCount(u32 count) {
    bool isOneDigit = count < 10;
    const char* digit1 = "PTotalTextD1";
    const char* digit2 = "PTotalTextD2";
    mFrame.paneByName(digit1).setVisibility(isOneDigit);
    mFrame.paneByName(digit2).setVisibility(!isOneDigit);
    mFrame.paneByName(isOneDigit ? digit1 : digit2)
        .setText(hel::common::FixedStringIN<char, 16>::FromFormat("%lu", count));
    mFrame.paneByName("PageN").setVisibility(count >= 2);
}

void FramePanel::changeOut(FrameIconKind icon) {
    if (_330 == icon) {
        mIcon.unsetParent();
        mIcon.setParent(mFrame.paneByName(T_FIX_NODE));
    } else {
        mIcon.unsetParent();
        mIcon.setParent(mFrame.paneByName(T_MOVE_NODE));
    }
    mFrame.setAnimByName("SwitchOut");
    mFrame.start(false);
    _32C = 1;
}

void FramePanel::changeIn(u32 page, FrameIconKind icon, const wchar_t* title) {
    changeNow(page, icon, title);
    mFrame.setAnimByName("SwitchIn");
    mFrame.start(false);
    _32C = 2;
}

void FramePanel::changeNow(u32 page, FrameIconKind icon, const wchar_t* title) {
    const char* anim;
    switch (icon) {
    case FRAME_ICON_KIND_DROPOUT:
        anim = "Dropout";
        break;
    case FRAME_ICON_KIND_SPECIAL:
        anim = "Special";
        break;
    case FRAME_ICON_KIND_SHIP:
        anim = "Ship";
        break;
    case FRAME_ICON_KIND_REMOTE:
        anim = "Remote";
        break;
    case FRAME_ICON_KIND_ABILITY:
        anim = "Ability";
        break;
    case FRAME_ICON_KIND_FRIEND:
        anim = "Friend";
        break;
    default:
        return;
    }
    mIcon.setAnimByName(anim);
    mIcon.start(false);
    mIcon.rootPane().show();
    if (icon == FRAME_ICON_KIND_ABILITY) {
        mAbilityIcon->rootPane().show();
    } else {
        mAbilityIcon->rootPane().hide();
    }
    u32 number = page + 1;
    bool isOneDigit = number < 10;
    const char* digit1 = "PCurrentTextD1";
    const char* digit2 = "PCurrentTextD2";
    mFrame.paneByName(digit1).setVisibility(isOneDigit);
    mFrame.paneByName(digit2).setVisibility(!isOneDigit);
    mFrame.paneByName(isOneDigit ? digit1 : digit2)
        .setText(hel::common::FixedStringIN<char, 16>::FromFormat("%lu", number));
    mFrame.paneByName("TitleText").setText(title);
    _330 = icon;
}

void FramePanel::updateFrame() {
    mFrame.updateFrame();
    if (_32C == 2 && mFrame.isAnimEnd()) {
        mFrame.setAnimByName("Wait");
        mFrame.start(true);
        _32C = 0;
    }
}

}  // namespace pause
