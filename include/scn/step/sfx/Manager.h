#ifndef SCN_STEP_SFX_MANAGER_H
#define SCN_STEP_SFX_MANAGER_H

#include "types.h"

namespace scn {
namespace step {
namespace sfx {

class ReverseWorld;
class SpiralScreen;

// TODO: members.
class Manager {
public:
    void beginDrawWarpImage();
    void endDrawWarpImage();
    ReverseWorld& reverseWorld();
    bool isForbiddenDrawWarp() const;
    void setFlagForbidDrawWarp(bool flag);
    SpiralScreen& spiralScreen();
};

}
}
}

#endif
