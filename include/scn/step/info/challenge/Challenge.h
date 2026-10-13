#ifndef SCN_STEP_INFO_CHALLENGE_CHALLENGE_H
#define SCN_STEP_INFO_CHALLENGE_CHALLENGE_H

#include "scn/step/info/challenge/Start.h"
#include "types.h"

namespace scn {
namespace step {
namespace info {
namespace challenge {

// TODO: the other members and functions; its size is not known.
class Challenge {
public:
    Start& start() { return mStart; }

private:
    u32 _0[0x191];
    Start mStart;
};

}
}
}
}

#endif
