#ifndef PAUSE_PAGESHIP_H
#define PAUSE_PAGESHIP_H

#include "lyt/Layout.h"
#include "mem/ExplicitAutoDeleteArray.h"
#include "pause/IPage.h"
#include "types.h"

namespace pause {

class Component;

class PageShip : public IPage {
public:
    class PartsLayout {
    public:
        PartsLayout(Component& component, lyt::Layout& parent, u32 index);

        void updateFrame();

    private:
        lyt::Layout mBase;
        lyt::Layout mParts;
    };

    PageShip(Component& component);

    virtual const wchar_t* pageFrameTitle() const;
    virtual lyt::Layout& pageMainLayout();
    virtual void pageProcAnim();
    virtual void pageProcHID();
    virtual bool pageIsBusy() const;

private:
    Component& mComponent;
    lyt::Layout mLayout;
    lyt::Layout mShip;
    lyt::Layout mShipPoint;
    lyt::Layout mSphere;
    mem::ExplicitAutoDeleteArray<PartsLayout, 5> mParts;
};

}  // namespace pause

#endif
