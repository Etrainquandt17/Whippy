#ifndef PAUSE_PAGEDROPOUT_H
#define PAUSE_PAGEDROPOUT_H

#include "info/common/Confirm.h"
#include "lyt/Layout.h"
#include "mem/ExplicitAutoDeleteArray.h"
#include "pause/ButtonPanel.h"
#include "pause/IPage.h"
#include "pause/WindowPanel.h"
#include "types.h"

namespace pause {

class Component;

class PageDropout : public IPage {
public:
    PageDropout(Component& component);

    virtual ~PageDropout();
    virtual const wchar_t* pageFrameTitle() const;
    virtual lyt::Layout& pageMainLayout();
    virtual void pageProcAnim();
    virtual void pageProcHID();
    virtual bool pageIsBusy() const;

private:
    void procHIDItemSelect();
    void procHIDItemDecide();
    void procHIDConfirm();

    Component& mComponent;
    lyt::Layout mLayout;
    WindowPanel mWindow;
    info::common::Confirm mConfirm;
    int _BBC;
    u32 mSelected;
    mem::ExplicitAutoDeleteArray<ButtonPanel, 3> mButtons;
};

}

#endif
