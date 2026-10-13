#ifndef HBM_HOMEBUTTONMENU_H
#define HBM_HOMEBUTTONMENU_H

#include "types.h"

namespace hbm {

class HomeButtonMenu {
public:
    HomeButtonMenu(bool flag);
    ~HomeButtonMenu();

    void onSoftReset();
    void disableMenu();
    void enableMenu();
    void setIgnore(bool ignore);

private:
    u8 _0[0x5D8];
};

}

#endif
