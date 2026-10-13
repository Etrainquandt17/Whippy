#ifndef APP_RESET_H
#define APP_RESET_H

#include "types.h"

namespace app {

class Reset {
public:
    Reset();
    ~Reset();

    void onSoftReset();

private:
    u8 _0[0x54];
};

}  // namespace app

#endif
