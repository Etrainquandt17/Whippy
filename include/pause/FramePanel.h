#ifndef PAUSE_FRAMEPANEL_H
#define PAUSE_FRAMEPANEL_H

#include "lyt/Layout.h"
#include "mem/ExplicitScopedPtr.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace pause {

class Component;

// Named after the animation of the icon layout that each plays.
enum FrameIconKind {
    FRAME_ICON_KIND_DROPOUT,
    FRAME_ICON_KIND_SPECIAL,
    FRAME_ICON_KIND_SHIP,
    FRAME_ICON_KIND_REMOTE,
    FRAME_ICON_KIND_FRIEND,
    FRAME_ICON_KIND_ABILITY,
};

class FramePanel {
public:
    FramePanel(Component& component);

    void reset();
    void setup();
    void setTotalPageCount(u32 count);
    void changeOut(FrameIconKind icon);
    void changeIn(u32 page, FrameIconKind icon, const wchar_t* title);
    void changeNow(u32 page, FrameIconKind icon, const wchar_t* title);
    void updateFrame();

private:
    Component& mComponent;
    lyt::Layout mFrame;
    lyt::Layout mIcon;
    mem::ExplicitScopedPtr<lyt::Layout> mAbilityIcon;
    // TODO: an enum; 1 while the frame switches out, 2 while it switches in.
    int _32C;
    FrameIconKind _330;
};

}  // namespace pause

#endif
