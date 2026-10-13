#ifndef SCN_STEP_HERO_ICE_STATESKATE_H
#define SCN_STEP_HERO_ICE_STATESKATE_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace ice {

// TODO: only what the common states call.
class StateSkate : public StateBase {
public:
    StateSkate(Hero* hero);
};

}
}
}
}

#endif
