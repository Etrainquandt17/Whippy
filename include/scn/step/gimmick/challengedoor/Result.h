#ifndef SCN_STEP_GIMMICK_CHALLENGEDOOR_RESULT_H
#define SCN_STEP_GIMMICK_CHALLENGEDOOR_RESULT_H

#include "hel/math/Vector2.h"
#include "scn/step/ChallengeKind.h"
#include "scn/step/SphereUnlockKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace gimmick {
namespace challengedoor {

class ChallengeDoor;

struct Result {
    Result();
    Result(const Result& other);

    bool _0;
    hel::math::Vector2 mPos;
    ChallengeKind mKind;
    ChallengeDoor* mDoor;
    SphereUnlockKind mUnlockKind;
};

}
}
}
}

#endif
