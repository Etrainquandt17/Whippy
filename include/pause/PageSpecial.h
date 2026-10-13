#ifndef PAUSE_PAGESPECIAL_H
#define PAUSE_PAGESPECIAL_H

#include "pause/IPage.h"
#include "types.h"

namespace pause {

class Component;

class PageSpecial : public IPage {
public:
    PageSpecial(Component& component);

    virtual const wchar_t* pageFrameTitle() const;
    virtual lyt::Layout& pageMainLayout();
    virtual void pageProcAnim();
    virtual void pageProcHID();
    virtual bool pageIsBusy() const;

private:
    u32 _4[0x65];
};

}  // namespace pause

#endif
