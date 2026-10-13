#ifndef SCN_STEP_GIMMICK_LVMAPDOOR_MANAGER_H
#define SCN_STEP_GIMMICK_LVMAPDOOR_MANAGER_H

#include "mem/ExplicitScopedPtr.h"
#include "types.h"

namespace scn {
namespace step {
namespace gimmick {
namespace lvmapdoor {

class DoorUnlockStar;

class Manager {
public:
    bool showDoorUnlockStarDemo() const;
    void disableDoorUnlockFlag();
    bool starPosSet();
    void disableInfoForDemo();
    void enableInfoForDemo();
    void disableInputs();
    void enableInputs();

    DoorUnlockStar& doorUnlockStar() { return mDoorUnlockStar.ref(); }

private:
    u32 _0[0xD];
    mem::ExplicitScopedPtr<DoorUnlockStar> mDoorUnlockStar;
};

}
}
}
}

#endif
