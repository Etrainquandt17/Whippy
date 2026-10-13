#ifndef PAUSE_WINDOWPANEL_H
#define PAUSE_WINDOWPANEL_H

#include "lyt/Layout.h"
#include "types.h"

namespace pause {

class Component;

class WindowPanel {
public:
    WindowPanel(Component& component, const lyt::PaneAccessor& pane, bool flag);

private:
    u32 _0;
    lyt::Layout mLayout;
};

}

#endif
