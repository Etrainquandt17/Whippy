#ifndef PAUSE_PAGEABILITY_H
#define PAUSE_PAGEABILITY_H

#include "lyt/Layout.h"
#include "pause/IPage.h"
#include "pause/ManualKind.h"
#include "types.h"
#include "util/PlacementNew.h"

namespace file {
class FileTree;
}

namespace pause {

class Component;

class PageAbility : public IPage {
public:
    PageAbility(Component& component, file::FileTree& fileTree, ManualKind kind);

    virtual const wchar_t* pageFrameTitle() const;
    virtual lyt::Layout& pageMainLayout();
    virtual void pageProcAnim();
    virtual void pageProcHID();
    virtual bool pageIsBusy() const;

private:
    Component& mComponent;
    lyt::Layout mLayout;
    util::PlacementNew<lyt::Layout> mImage;
};

}

#endif
