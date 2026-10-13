#ifndef PAUSE_PAGEMANAGER_H
#define PAUSE_PAGEMANAGER_H

#include "file/FileTree.h"
#include "hel/common/MutableArray.h"
#include "lyt/Layout.h"
#include "mem/AutoHeapExp.h"
#include "mem/ExplicitScopedPtr.h"
#include "pause/ContextOpen.h"
#include "pause/CursorPanel.h"
#include "pause/FramePanel.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace pause {

class Component;
class IPage;

class PageManager {
public:
    enum PageKind {
        PAGE_KIND_DROPOUT,
        PAGE_KIND_SPECIAL,
        PAGE_KIND_ABILITY,
        PAGE_KIND_COMMAND,
        PAGE_KIND_COMMAND_FRIEND,
        PAGE_KIND_SHIP,
        PAGE_KIND_REMOTE,
    };

    struct PageRecipe {
        static PageRecipe Create(PageKind kind, u32 arg);

        PageKind mKind;
        u32 mArg;
    };

    PageManager(Component& component);
    ~PageManager();

    void reset();
    void setup();
    bool isPageChanging() const;
    bool isBusy() const;
    void procAnim();
    void procHID();
    bool hasMultiPage() const;
    IPage* currentPage();
    void setupCurrentPage();
    void changePage(u32 page, bool isNext);
    FrameIconKind currentPageFrameIcon() const;

private:
    Component& mComponent;
    mem::AutoHeapExp mHeap;
    file::FileTree mFileTree;
    // TODO: an enum; 1 to 3 while the page changes.
    int _A4;
    u32 mPage;
    bool mIsNext;
    bool _AD;
    ContextOpen mContextOpen;
    util::FrameCounter _C4;
    lyt::Layout mLayout;
    CursorPanel _25C;
    CursorPanel _3F8;
    mem::ExplicitScopedPtr<IPage> mCurrentPage;
    hel::common::MutableArray<PageRecipe, 10> mRecipes;
};

}  // namespace pause

#endif
