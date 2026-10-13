#include "pause/PageAbility.h"

#include "app/Message.h"
#include "file/FileAccessor.h"
#include "file/FileTree.h"
#include "hel/common/FixedStringIN.h"
#include "lyt/LayoutContext.h"
#include "metafortress.h"
#include "pause/Component.h"
#include "pause/Constant.h"
#include "pause/ManualData.h"
#include "util/ObjList.h"

namespace pause {

PageAbility::PageAbility(Component& component, file::FileTree& fileTree, ManualKind kind)
    : mComponent(component)
    , mLayout(lyt::LayoutContext(Constant::LytResPathPage(PAGE_RES_KIND_2), "AbilityWindow", component.allocator()))
    , mImage() {
    hel::common::FixedStringIN<char, 48> path = ManualData::PathAbilityBG(kind);
    {
        file::FileAccessor accessor(hel::common::FixedStringIN<char, 80>::FromFormat("lyt/%s.arc.cmpbin", static_cast<const char*>(path)), false);
        fileTree.addFile(accessor.block(), hel::common::FixedStringIN<char, 80>::FromFormat("lyt/%s.arc.cmp", static_cast<const char*>(path)), 0);
    }
    mImage.construct(lyt::LayoutContext(path, "AbImage", component.allocator()));
    mImage->setParent(mLayout.paneByName("ImageN"));
    mLayout.paneByName("AbText").setText(
        app::Message::TextPause(ManualData::LabelAbilityInfo(kind, component.contextInit().modeKind())));
}

const wchar_t* PageAbility::pageFrameTitle() const {
    return app::Message::TextPause(hel::common::FixedStringIN<char, 32>::FromFormat(
        "%s0", static_cast<const char*>(ManualData::LabelFrameAbiilityTitle(mComponent.contextOpen().manualKind()))));
}

lyt::Layout& PageAbility::pageMainLayout() {
    return mLayout;
}

void PageAbility::pageProcAnim() {
    mLayout.updateFrame();
}

void PageAbility::pageProcHID() {}

#define MF_FUNCTION pageIsBusy__Q25pause11PageAbilityCFv
bool PageAbility::pageIsBusy() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  0x84D95180
        opword  0x97DD700A
        opword  MF_WORD(0x20)
        opword  0xECFE2F80
        opword  0xB4D17781
        opword  MF_WORD(0x2C)
        opword  0x386B8690
    after1:
        mflr    r19
        lwz     r14, 0x8(r19)
        lwz     r15, 0x14(r19)
        stw     r14, start
        add     r15, r14, r15
        stw     r15, end
        bl      after2
        opword  MF_WORD(0x50)
        opword  0xBEF58B0C
    after2:
        mflr    r17
        lwz     r22, 0x0(r17)
        stw     r22, expected
    }
    hash = 0x811C9E53;
    limit = end - start + 1;
    i = 1;
    last = end - 1;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(last - i);
        hash *= 0x010001D1;
    }
    return expected != hash;
}
#undef MF_FUNCTION

}  // namespace pause
