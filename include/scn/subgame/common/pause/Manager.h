#ifndef SCN_SUBGAME_COMMON_PAUSE_MANAGER_H
#define SCN_SUBGAME_COMMON_PAUSE_MANAGER_H

#include "types.h"

namespace scn {
namespace subgame {
namespace common {
namespace pause {

class Manager {
public:
    void requestLockPause();
    void requestUnlockPause();
    void requestLockPauseSE();
    void requestUnlockPauseSE();
};

}
}
}
}

#endif
