#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE

#include "pause/PageManager.h"

#include "app/Application.h"
#include "file/FileAccessor.h"
#include "file/FileManager.h"
#include "hel/common/ExplicitSingleton.h"
#include "hel/common/FixedString.h"
#include "lyt/LayoutContext.h"
#include "mem/HeapCompaction.h"
#include "mem/Memory.h"
#include "metafortress.h"
#include "pause/Component.h"
#include "pause/Constant.h"
#include "pause/HID.h"
#include "pause/IPage.h"
#include "pause/ManualData.h"
#include "pause/PageAbility.h"
#include "pause/PageCommand.h"
#include "pause/PageDropout.h"
#include "pause/PageRemote.h"
#include "pause/PageShip.h"
#include "pause/PageSpecial.h"
#include "pause/ResultSetter.h"
#include "std/tr1/reference_wrapper.h"
#include "util/ObjList.h"

using app::Application;
using hel::common::ExplicitSingleton;
using hel::common::FixedString;

namespace pause {

namespace {

const char* const T_MOVE_NODE_NAME = "WindowN";
const char* const T_FIX_NODE_NAME = "WindowFixN";

bool tBtnCheck(const hid::Button& btn, bool repeats, u32 mask) {
    return btn.isTrigger(mask) || (btn.isHold(mask) && repeats);
}

// TODO: the two are expanded in setup(), one each, and nothing is left of their names.
bool tHasPageShip(Component& component) {
    switch (component.contextInit().modeKind()) {
    case MODE_KIND_0:
    case MODE_KIND_1:
    case MODE_KIND_2:
    case MODE_KIND_3:
    case MODE_KIND_4:
        return true;
    default:
        return false;
    }
}

bool tHasPageRemote(Component& component) {
    switch (component.contextInit().modeKind()) {
    case MODE_KIND_0:
    case MODE_KIND_1:
    case MODE_KIND_2:
    case MODE_KIND_3:
    case MODE_KIND_4:
        return true;
    default:
        return false;
    }
}

}

#define MF_FUNCTION __ct__Q25pause11PageManagerFRQ25pause9Component
// TODO: mem::HeapExp is a mem::IAllocator; its header does not say so yet.
PageManager::PageManager(Component& component)
    : mComponent(component)
    , mHeap(ExplicitSingleton<mem::Memory>::object_->externalHeap(), 0xC8000, "PausePage")
    , mFileTree(component.allocator(), reinterpret_cast<mem::IAllocator&>(mHeap.obj()), 2, 0)
    , _A4(0)
    , mPage(0)
    , mIsNext(false)
    , _AD(false)
    , mContextOpen()
    , _C4(15)
    , mLayout(lyt::LayoutContext(Constant::LytResPathMain(), "PauseCursorBase", component.allocator()))
    , _25C(component, "PauseCursorL", mLayout, mLayout.paneByName("CursorLN"))
    , _3F8(component, "PauseCursorR", mLayout, mLayout.paneByName("CursorRN"))
    , mCurrentPage(component.allocator())
    , mRecipes() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x150)
        opword  0x808AA292
        opword  MF_WORD(0x158)
    after1:
        mflr    r28
        lwz     r18, 0x0(r28)
        stw     r18, start
        lwz     r22, 0x8(r28)
        add     r18, r18, r22
        stw     r18, end
    }
    mFileTree.setParent(ExplicitSingleton<Application>::object_->fileManager().treeRoot());
    limit = end - start + 1;
    base = start;
    mLayout.setParent(mComponent.base().paneByName("PauseCursorN"));
    asm {
        bl      after2
        opword  MF_WORD(0x1D4)
        opword  0x5B88B7EF
    after2:
        mflr    r28
        lwz     r22, 0x0(r28)
        stw     r22, expected
    }
    mLayout.setAnimByName("Wait");
    hash = 0;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash *= 107;
        hash += *(u16*)(base + i - 1);
    }
    mLayout.start(expected == hash);
}
#undef MF_FUNCTION

PageManager::~PageManager() {}

void PageManager::reset() {
    mCurrentPage.destruct();
    mRecipes.clear();
}

#define MF_FUNCTION setup__Q25pause11PageManagerFv
void PageManager::setup() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 last;
    ManualKind manual;

    if (!_AD || !mContextOpen.isSamePageLayout(mComponent.contextOpen())) {
        mPage = 0;
    }
    mContextOpen = mComponent.contextOpen();
    _AD = true;
    hash = 0xB5;
    if (!mComponent.contextOpen().commandPageOnly()) {
        mRecipes.add(PageRecipe::Create(PAGE_KIND_DROPOUT, 0));
    }
    asm {
        bl      after1
        opword  MF_WORD(0xD4)
        opword  MF_WORD(0xD8)
    after1:
        mflr    r28
        lwz     r22, 0x0(r28)
        lwz     r25, 0x4(r28)
        add     r22, r22, r28
        add     r25, r25, r22
        stw     r22, start
        stw     r25, end
    }
    if (mComponent.contextInit().specialKind() != SPECIAL_KIND_11) {
        mRecipes.add(PageRecipe::Create(PAGE_KIND_SPECIAL, 0));
    }
    manual = mComponent.contextOpen().manualKind();
    last = end;
    word = start;
    if (manual != MANUAL_KIND_35) {
        if (!mComponent.contextOpen().commandPageOnly()) {
            mRecipes.add(PageRecipe::Create(PAGE_KIND_ABILITY, 0));
            for (u32 i = 0; i < ManualData::CommandPageCount(manual); i++) {
                mRecipes.add(PageRecipe::Create(PAGE_KIND_COMMAND, i));
            }
            if (mComponent.contextOpen().addFriendPage()) {
                mRecipes.add(PageRecipe::Create(PAGE_KIND_COMMAND_FRIEND, 0));
            }
        } else {
            for (u32 i = 0; i < ManualData::CommandPageCount(manual); i++) {
                mRecipes.add(PageRecipe::Create(PAGE_KIND_COMMAND, i));
            }
        }
    }
    for (;;) {
        if (word == last) {
            break;
        }
        hash = *(u16*)word ^ (hash << 4 ^ hash >> 28);
        word += 2;
    }
    if (tHasPageShip(mComponent) && !mComponent.contextOpen().commandPageOnly()) {
        mRecipes.add(PageRecipe::Create(PAGE_KIND_SHIP, 0));
    }
    asm {
        bl      after2
        opword  MF_WORD(0x2F8)
        opword  0x60006922
    after2:
        mflr    r27
        lwz     r19, 0x0(r27)
        stw     r19, expected
    }
    if (tHasPageRemote(mComponent) && !mComponent.contextOpen().commandPageOnly()) {
        mRecipes.add(PageRecipe::Create(PAGE_KIND_REMOTE, 0));
    }
    hash += hash << 3;
    mComponent.framePanel().setTotalPageCount(mRecipes.count());
    mLayout.rootPane().setVisibility(mRecipes.count() >= 2);
    hash ^= hash >> 11;
    setupCurrentPage();
    currentPage()->pageMainLayout().setParent(mComponent.base().paneByName(T_FIX_NODE_NAME));
    hash += hash << 15;
    mComponent.framePanel().changeNow(mPage, currentPageFrameIcon(), currentPage()->pageFrameTitle());
    word = expected;
    if (hash != word) {
        volatile u32 base2;
        volatile u32 addend;
        volatile u32 offset;
        volatile u32 response;

        asm {
            bl      after3
            opword  MF_WORD(0x480)
        after3:
            mflr    r16
            lwz     r19, 0x0(r16)
            stw     r19, -0x4(r1)
            stw     r16, 0x0(r1)
            stw     r19, -0x4(r1)
            stw     r16, -0x8(r1)
            mtlr    r19
            bl      after4
            opword  MF_WORD(0x4A4)
            opword  0xBC254880
            opword  0xA8CEA193
            opword  MF_WORD(0x4B0)
        after4:
            mflr    r16
            lwz     r14, 0xc(r16)
            stw     r14, addend
            lwz     r14, 0x0(r16)
            stw     r16, base2
            stw     r14, offset
        }
        offset = offset + 0x42;
        response = offset ^ addend;
        response = response + base2;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    } else {
        _C4.setEndIfNotEnd();
    }
}
#undef MF_FUNCTION

bool PageManager::isPageChanging() const {
    return _A4 != 0;
}

bool PageManager::isBusy() const {
    return isPageChanging() || const_cast<PageManager*>(this)->currentPage()->pageIsBusy();
}

void PageManager::procAnim() {
    if (!isPageChanging() && !isBusy()) {
        mLayout.updateFrame();
    }
    if (!currentPage()->pageIsBusy()) {
        _C4.advanceIfNotEnd();
        _25C.updateFrame();
        _3F8.updateFrame();
    }
    currentPage()->pageProcAnim();
}

void PageManager::procHID() {
    if (_A4 == 1) {
        if (!mComponent.base().isAnimating()) {
            _A4 = 2;
        }
        return;
    }
    if (_A4 == 2) {
        const char* anim;

        setupCurrentPage();
        currentPage()->pageMainLayout().setParent(mComponent.base().paneByName(T_MOVE_NODE_NAME));
        if (mIsNext) {
            anim = "NextPage2";
        } else {
            anim = "PrevPage2";
        }
        mComponent.base().play(anim);
        mComponent.framePanel().changeIn(mPage, currentPageFrameIcon(), currentPage()->pageFrameTitle());
        _A4 = 3;
        return;
    }
    if (_A4 == 3) {
        if (mComponent.base().isAnimating()) {
            return;
        }
        currentPage()->pageMainLayout().unsetParent();
        currentPage()->pageMainLayout().setParent(mComponent.base().paneByName(T_FIX_NODE_NAME));
        _25C.startAnimToFreeIfPushed();
        _3F8.startAnimToFreeIfPushed();
        _C4.reset();
        _A4 = 0;
    }
    if (!mComponent.resultSetter().wasSet() && hasMultiPage() && !currentPage()->pageIsBusy()) {
        hid::Button btn = mComponent.hid().btn();
        if (tBtnCheck(btn, _C4.isEnd(), 8)) {
            changePage(mPage != 0 ? mPage - 1 : mRecipes.count() - 1, false);
            return;
        }
        if (tBtnCheck(btn, _C4.isEnd(), 4)) {
            u32 next = mPage + 1;
            changePage(next < mRecipes.count() ? next : 0, true);
            return;
        }
    }
    currentPage()->pageProcHID();
}

bool PageManager::hasMultiPage() const {
    return mRecipes.count() > 1;
}

IPage* PageManager::currentPage() {
    return &mCurrentPage.ref();
}

void PageManager::setupCurrentPage() {
    mCurrentPage.destruct();
    mFileTree.clearFiles();
    PageRecipe recipe = mRecipes[mPage];
    const PageResKind res[] = {
        PAGE_RES_KIND_0, PAGE_RES_KIND_1, PAGE_RES_KIND_2, PAGE_RES_KIND_3,
        PAGE_RES_KIND_3, PAGE_RES_KIND_4, PAGE_RES_KIND_0,
    };
    FixedString<80> path =
        FixedString<80>::FromFormat("lyt/%s.arc", Constant::LytResPathPage(res[recipe.mKind]));
    FixedString<80> cmpbin =
        FixedString<80>::FromFormat("%s.cmpbin", static_cast<const char*>(path));
    FixedString<80> cmp = FixedString<80>::FromFormat("%s.cmp", static_cast<const char*>(path));
    {
        file::FileAccessor accessor(cmpbin, false);
        mFileTree.addFile(accessor.block(), cmp, 0);
    }
    switch (recipe.mKind) {
    case PAGE_KIND_DROPOUT:
        mCurrentPage.constructE<PageDropout>(std::tr1::ref(mComponent));
        break;
    case PAGE_KIND_SPECIAL:
        mCurrentPage.constructE<PageSpecial>(std::tr1::ref(mComponent));
        break;
    case PAGE_KIND_ABILITY:
        mCurrentPage.constructE<PageAbility>(std::tr1::ref(mComponent), std::tr1::ref(mFileTree),
                                             mComponent.contextOpen().manualKind());
        break;
    case PAGE_KIND_COMMAND:
        mCurrentPage.constructE<PageCommand>(std::tr1::ref(mComponent), mComponent.contextOpen().manualKind(),
                                             recipe.mArg);
        break;
    case PAGE_KIND_COMMAND_FRIEND:
        mCurrentPage.constructE<PageCommand>(std::tr1::ref(mComponent), MANUAL_KIND_34, recipe.mArg);
        break;
    case PAGE_KIND_SHIP:
        mCurrentPage.constructE<PageShip>(std::tr1::ref(mComponent));
        break;
    case PAGE_KIND_REMOTE:
        mCurrentPage.constructE<PageRemote>(std::tr1::ref(mComponent));
        break;
    }
}

#define MF_FUNCTION changePage__Q25pause11PageManagerFUlb
void PageManager::changePage(u32 page, bool isNext) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    const char* anim;
    u32 i;
    u32 base;
    u32 limit;

    hash = 0;
    mIsNext = isNext;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0xBB35305C
    after1:
        mflr    r29
        lwz     r14, 0x0(r29)
        stw     r14, expected
    }
    mPage = page;
    if (isNext) {
        anim = "NextPage1";
    } else {
        anim = "PrevPage1";
    }
    mComponent.base().play(anim);
    asm {
        bl      after2
        opword  0x112D9905
        opword  MF_WORD(0x78)
        opword  0xF17E5600
        opword  0xC580330E
        opword  MF_WORD(0x84)
        opword  0xF8A5B780
    after2:
        mflr    r25
        lwz     r29, 0x10(r25)
        lwz     r28, 0x4(r25)
        stw     r28, end
        stw     r29, start
    }
    currentPage()->pageMainLayout().unsetParent();
    i = 1;
    base = start;
    limit = end - base + 1;
    currentPage()->pageMainLayout().setParent(mComponent.base().paneByName(T_MOVE_NODE_NAME));
    for (; i != limit; i += 2) {
        hash += *(u16*)(base + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    mComponent.framePanel().changeOut(currentPageFrameIcon());
    if (hash - expected == 0 && isNext) {
        _3F8.startAnimToPush();
    } else {
        _25C.startAnimToPush();
    }
    mComponent.seReq().start(0x7F);
    _A4 = 1;
}
#undef MF_FUNCTION

FrameIconKind PageManager::currentPageFrameIcon() const {
    switch (mRecipes[mPage].mKind) {
    case PAGE_KIND_DROPOUT:
        return FRAME_ICON_KIND_DROPOUT;
    case PAGE_KIND_SPECIAL:
        return FRAME_ICON_KIND_SPECIAL;
    case PAGE_KIND_ABILITY:
        return FRAME_ICON_KIND_ABILITY;
    case PAGE_KIND_COMMAND:
        return FRAME_ICON_KIND_ABILITY;
    case PAGE_KIND_COMMAND_FRIEND:
        return FRAME_ICON_KIND_FRIEND;
    case PAGE_KIND_SHIP:
        return FRAME_ICON_KIND_SHIP;
    case PAGE_KIND_REMOTE:
        return FRAME_ICON_KIND_REMOTE;
    default:
        return FRAME_ICON_KIND_DROPOUT;
    }
}

PageManager::PageRecipe PageManager::PageRecipe::Create(PageKind kind, u32 arg) {
    PageRecipe recipe;
    recipe.mKind = kind;
    recipe.mArg = arg;
    return recipe;
}

}  // namespace pause
