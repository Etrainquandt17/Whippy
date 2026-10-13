#define MEM_EXPLICITAUTODELETEARRAY_INLINE

#include "pause/PageShip.h"

#include "app/Application.h"
#include "app/Message.h"
#include "hel/common/ExplicitSingleton.h"
#include "hel/common/FixedStringIN.h"
#include "lyt/LayoutContext.h"
#include "metafortress.h"
#include "pause/Component.h"
#include "pause/Constant.h"
#include "scn/step/StageKindUtil.h"
#include "std/tr1/reference_wrapper.h"
#include "storage/BackupFileData.h"
#include "storage/StorageManager.h"
#include "storage/StoryData.h"
#include "util/ObjList.h"

namespace pause {

namespace {

const char* T_PARTS_NAMES[] = {
    "OllN", "WingRN", "WingLN", "ShipTopN", "MustN",
};

storage::StoryData& tStoryData(Component& component) {
    return hel::common::ExplicitSingleton<app::Application>::Object()
        .storageManager()
        .selectedBackupFileData()
        .storyData(component.contextInit().storyMode());
}

u32 tClearedCount(Component& component) {
    storage::StoryData& data = tStoryData(component);
    u32 i;
    for (i = 0; i < 7; i++) {
        if (!data.levelData(static_cast<scn::step::LevelKind>(i))._4) {
            break;
        }
    }
    return i;
}

u32 tSphereCount(Component& component) {
    return tStoryData(component).sphereGetCount() + component.contextOpen().getSphereCountInCurrentStage();
}

}

PageShip::PageShip(Component& component)
    : mComponent(component)
    , mLayout(lyt::LayoutContext(Constant::LytResPathPage(PAGE_RES_KIND_4), "ShipWindow", component.allocator()))
    , mShip(lyt::LayoutContext(Constant::LytResPathPage(PAGE_RES_KIND_4), "Ship", component.allocator()))
    , mShipPoint(lyt::LayoutContext(Constant::LytResPathPage(PAGE_RES_KIND_4), "ShipPoint", component.allocator()))
    , mSphere(lyt::LayoutContext(Constant::LytResPathPage(PAGE_RES_KIND_4), "Sphere", component.allocator()))
    , mParts(component.allocator()) {
    for (u32 i = 0; i < 5; i++) {
        mParts.add(std::tr1::ref(component), std::tr1::ref(mLayout), i);
    }
    mSphere.paneByName("MolecularText")
        .setText(hel::common::FixedStringIN<char, 16>::FromFormat("%lu", tSphereCount(component)));
    mSphere.paneByName("DenominatorText")
        .setText(hel::common::FixedStringIN<char, 16>::FromFormat("%lu", scn::step::StageKindUtil::SphereTotalNum()));
    mShip.setParent(mLayout.paneByName("ShipN"));
    mShipPoint.setParent(mLayout.paneByName("ShipPointN"));
    mSphere.setParent(mLayout.paneByName("SphereN"));
    mShipPoint.setAnimByName("Wait");
    mShipPoint.start(true);
    const char* anim;
    switch (tClearedCount(component)) {
    case 0:
        anim = "Wait01";
        break;
    case 1:
        anim = "Wait02";
        break;
    case 2:
        anim = "Wait03";
        break;
    case 3:
        anim = "Wait04";
        break;
    case 4:
        anim = "Wait05";
        break;
    default:
        anim = "Wait06";
        break;
    }
    mShip.setAnimByName(anim);
    mShip.start(true);
}

const wchar_t* PageShip::pageFrameTitle() const {
    return app::Message::TextPause("PageTitleShip");
}

lyt::Layout& PageShip::pageMainLayout() {
    return mLayout;
}

#define MF_FUNCTION pageProcAnim__Q25pause8PageShipFv
void PageShip::pageProcAnim() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xDE1E3703
        opword  0x586DED90
        opword  MF_WORD(0x30)
        opword  0xAC3C2391
    after1:
        mflr    r24
        lwz     r16, 0x0(r24)
        add     r16, r16, r24
        lwz     r18, 0xc(r24)
        stw     r16, start
        add     r18, r18, r16
        stw     r18, end
    }
    mLayout.updateFrame();
    i = 1;
    base = start;
    limit = end - base + 1;
    hash = 0xBF;
    mShip.updateFrame();
    for (;;) {
        if (i == limit) {
            break;
        }
        hash = (hash << 4 ^ hash >> 28) ^ *(u16*)(base + i - 1);
        i += 2;
    }
    mShipPoint.updateFrame();
    asm {
        bl      after2
        opword  MF_WORD(0xB0)
        opword  0xB189E60D
    after2:
        mflr    r27
        lwz     r21, 0x0(r27)
        stw     r21, expected
    }
    hash ^= hash >> 10;
    mSphere.updateFrame();
    limit = hash << 20;
    hash ^= limit;
    limit = expected;
    base = limit & ~hash;
    limit = expected;
    hash = hash & ~limit;
    hash = base | hash;
    limit = hash << 3;
    hash = hash | limit;
    if (hash == 0) {
        for (hash = 0; hash < mParts.count(); hash++) {
            mParts[hash].updateFrame();
        }
    } else {
        volatile u32 offset;
        volatile u32 base2;
        volatile u32 response;
        volatile u32 addend;

        asm {
            bl      after3
            opword  0x743CE393
            opword  MF_WORD(0x144)
        after3:
            mflr    r30
            lwz     r29, 0x4(r30)
            stw     r29, -0x4(r1)
            stw     r30, 0x0(r1)
            stw     r29, -0x4(r1)
            stw     r30, -0x8(r1)
            mtlr    r29
            bl      after4
            opword  MF_WORD(0x168)
            opword  MF_WORD(0x16C)
        after4:
            mflr    r27
            stw     r27, base2
            lwz     r14, 0x0(r27)
            stw     r14, offset
            lwz     r24, 0x4(r27)
            stw     r24, addend
        }
        offset = offset - 0xCB;
        response = offset - addend;
        response = response + base2;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    }
}
#undef MF_FUNCTION

void PageShip::pageProcHID() {}

#define MF_FUNCTION pageIsBusy__Q25pause8PageShipCFv
bool PageShip::pageIsBusy() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 value;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0xE4F92590
        opword  0x0E7D6505
        opword  MF_WORD(0x2C)
    after1:
        mflr    r14
        lwz     r21, 0x0(r14)
        stw     r21, start
        lwz     r28, 0xC(r14)
        add     r21, r21, r28
        stw     r21, end
    }
    i = start;
    value = end;
    value = value - i;
    limit = value + 1;
    i = 1;
    base = start;
    hash = 0;
    while (i != limit) {
        hash = hash * 61;
        value = base + i;
        value = *(u16*)(value - 1);
        hash = hash + value;
        i = i + 2;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x88)
        opword  0xBAFA1B10
    after2:
        mflr    r29
        lwz     r26, 0x0(r29)
        stw     r26, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    return expected != hash;
}
#undef MF_FUNCTION

PageShip::PartsLayout::PartsLayout(Component& component, lyt::Layout& parent, u32 index)
    : mBase(lyt::LayoutContext(Constant::LytResPathPage(PAGE_RES_KIND_4), "ShipPartBase", component.allocator()))
    , mParts(lyt::LayoutContext(Constant::LytResPathPage(PAGE_RES_KIND_4), "ShipParts", component.allocator())) {
    bool isCleared = index < tClearedCount(component);
    const char* anim = isCleared ? "Wait02" : "Wait01";
    mBase.setAnimByName(anim);
    mBase.start(true);
    mParts.setAnimByName(anim);
    mParts.start(true);
    mBase.setParent(parent.paneByName(T_PARTS_NAMES[index]));
    mParts.setParent(mBase.paneByName("PartsN"));
    for (u32 i = 0; i < 5; i++) {
        if (i != index) {
            mParts.paneByName(T_PARTS_NAMES[i]).setVisibility(false);
        }
    }
}

void PageShip::PartsLayout::updateFrame() {
    mBase.updateFrame();
    mParts.updateFrame();
}

}
