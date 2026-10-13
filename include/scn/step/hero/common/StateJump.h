#ifndef SCN_STEP_HERO_COMMON_STATEJUMP_H
#define SCN_STEP_HERO_COMMON_STATEJUMP_H

#include "gobj/Move.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/StateBase.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/vacuum/Attacker.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateJump : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);
    static bool TryToChangeState(Hero* hero, bool initSpeed);

    StateJump(Hero* hero, bool initSpeed = true, bool = false);
    StateJump(Hero* hero, u32 frame, bool initSpeed = true, bool = false);
    virtual ~StateJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void construct(bool initSpeed);
    bool doEnableRotAnim() const;

    bool isHandFree() const {
        return obj().vacuumAttacker().vacuumCount() == 0 && !obj().carryItemUser().isItemExist();
    }
    bool isNotLiftUp() const { return isHandFree() && !obj().model().subAnimControl().isLiftUpRHand(); }
    bool isAlone() const { return isNotLiftUp() && !obj().piggyback().isExistChild(); }
    bool isSafe() const { return isAlone() && !obj().stateChecker().isBombDanger(); }

    u32 mFrame;
    u32 mHoldFrame;
    bool _10;
};

}
}
}
}

#endif
