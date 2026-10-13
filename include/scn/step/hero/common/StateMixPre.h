#ifndef SCN_STEP_HERO_COMMON_STATEMIXPRE_H
#define SCN_STEP_HERO_COMMON_STATEMIXPRE_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateMixPre : public StateBase {
public:
    StateMixPre(Hero* hero);
    virtual ~StateMixPre();
    virtual void procAnim();
};

}
}
}
}

#endif
