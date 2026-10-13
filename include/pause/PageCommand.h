#ifndef PAUSE_PAGECOMMAND_H
#define PAUSE_PAGECOMMAND_H

#include "pause/IPage.h"
#include "pause/ManualKind.h"
#include "types.h"

namespace pause {

class Component;

class PageCommand : public IPage {
public:
    PageCommand(Component& component, ManualKind kind, u32 page);

    virtual const wchar_t* pageFrameTitle() const;
    virtual lyt::Layout& pageMainLayout();
    virtual void pageProcAnim();
    virtual void pageProcHID();
    virtual bool pageIsBusy() const;

private:
    u32 _4[0x72];
};

}

#endif
