#ifndef SCN_STEP_SFX_REVERSEWORLD_H
#define SCN_STEP_SFX_REVERSEWORLD_H

#include "types.h"

namespace scn {
namespace step {
namespace sfx {

// TODO: members.
class ReverseWorld {
public:
    void startAnim(u32 kind);
    void startAnim(u32 kind, bool);
};

}
}
}

#endif
