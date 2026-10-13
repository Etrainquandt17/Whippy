#ifndef PAUSE_CURSORPANEL_H
#define PAUSE_CURSORPANEL_H

#include "lyt/Layout.h"
#include "types.h"

namespace pause {

class Component;

class CursorPanel {
public:
    CursorPanel(Component& component, const char* name, const lyt::Layout& parent, const lyt::PaneAccessor& pane);

    void startAnimToPush();
    void startAnimToFreeIfPushed();
    void updateFrame();

private:
    u32 _0[0x2];
    lyt::Layout mLayout;
    u32 _198;
};

}

#endif
