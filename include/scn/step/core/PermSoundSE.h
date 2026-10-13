#ifndef SCN_STEP_CORE_PERMSOUNDSE_H
#define SCN_STEP_CORE_PERMSOUNDSE_H

#include "types.h"

namespace scn {
namespace step {

class Component;

namespace core {

// TODO: members.
class PermSoundSE {
public:
    PermSoundSE(Component& component);
    ~PermSoundSE();

    void start(u32 id);
    void stop();
};

}
}
}

#endif
