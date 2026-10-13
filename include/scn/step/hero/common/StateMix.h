#ifndef SCN_STEP_HERO_COMMON_STATEMIX_H
#define SCN_STEP_HERO_COMMON_STATEMIX_H

#include "ostop/ReqHandle.h"
#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

// TODO: the rest of the class, when the unit is written.
class StateMix : public StateBase {
public:
    StateMix(Hero* hero, const ::ostop::ReqHandle& handle);
};

}
}
}
}

#endif
