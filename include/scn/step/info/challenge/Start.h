#ifndef SCN_STEP_INFO_CHALLENGE_START_H
#define SCN_STEP_INFO_CHALLENGE_START_H

#include "scn/step/ChallengeKind.h"

namespace scn {
namespace step {
namespace info {
namespace challenge {

// TODO: the members and the other functions.
class Start {
public:
    void appear(ChallengeKind kind);
    bool isAnimEnd() const;
};

}
}
}
}

#endif
