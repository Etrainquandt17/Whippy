#ifndef PAUSE_PAGEREMOTE_H
#define PAUSE_PAGEREMOTE_H

#include "pause/IPage.h"
#include "types.h"

namespace pause {

class Component;

class PageRemote : public IPage {
public:
    PageRemote(Component& component);

    virtual const wchar_t* pageFrameTitle() const;
    virtual lyt::Layout& pageMainLayout();
    virtual void pageProcAnim();
    virtual void pageProcHID();
    virtual bool pageIsBusy() const;

private:
    u32 _4[0x130];
};

}

#endif
