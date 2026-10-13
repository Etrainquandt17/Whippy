#ifndef SCN_STEP_HERO_COMMON_STATEWATERWAIT_H
#define SCN_STEP_HERO_COMMON_STATEWATERWAIT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateWaterWait : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);
    static bool TryToChangeStateWithScript(Hero* hero, u32 script);

    StateWaterWait(Hero* hero);
    StateWaterWait(Hero* hero, u32 script);
    virtual ~StateWaterWait();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void construct(u32 script);
};

}
}
}
}

#endif
