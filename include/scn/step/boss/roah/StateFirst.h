#ifndef SCN_STEP_BOSS_ROAH_STATEFIRST_H
#define SCN_STEP_BOSS_ROAH_STATEFIRST_H

#include "hel/geo/Rect.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateFirst : public StateBase {
public:
    StateFirst(Boss* boss);
    virtual ~StateFirst();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::geo::Rect mStartRect;
    hel::geo::Rect mGoalRect;
};

}
}
}
}

#endif
