#ifndef APP_HIDERRORMENU_H
#define APP_HIDERRORMENU_H

#include "types.h"

namespace app {

class HIDErrorMenu {
public:
    // TODO: name the modes.
    enum DisconnectMenuMode {
        DISCONNECT_MENU_MODE_0,
        DISCONNECT_MENU_MODE_1,
        DISCONNECT_MENU_MODE_2,
    };

    void setup(DisconnectMenuMode mode);
    void setIsEnable(bool enable);
    void setIsMainPlayerOnly(bool mainPlayerOnly);
    void setWatchEnable(u32 index, bool enable);
};

}

#endif
