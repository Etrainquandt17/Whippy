#ifndef PAUSE_BUTTONPANEL_H
#define PAUSE_BUTTONPANEL_H

#include "lyt/Layout.h"
#include "types.h"

namespace pause {

class Component;

class ButtonPanel {
public:
    ButtonPanel(Component& component, const char* name, const lyt::PaneAccessor& pane, const wchar_t* text, bool flag);

    void setSelected();
    void setNotSelected();
    void decide();
    bool isDecideAnimEnd() const;
    bool isEnable() const;
    void updateFrame();

private:
    u32 _0;
    u32 _4;
    lyt::Layout mLayout;
};

}  // namespace pause

#endif
