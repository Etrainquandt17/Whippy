#ifndef SCN_STEP_HERO_RIDE_STATESTEPSHOEWAIT_H
#define SCN_STEP_HERO_RIDE_STATESTEPSHOEWAIT_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace ride {

// TODO: only what the common states call.
class StateStepShoeWait : public StateBase {
public:
    StateStepShoeWait(Hero* hero);
    StateStepShoeWait(Hero* hero, bool);
};

}
}
}
}

#endif
