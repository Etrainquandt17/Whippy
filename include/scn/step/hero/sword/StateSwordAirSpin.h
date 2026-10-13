#ifndef SCN_STEP_HERO_SWORD_STATESWORDAIRSPIN_H
#define SCN_STEP_HERO_SWORD_STATESWORDAIRSPIN_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordAirSpin : public StateBase {
public:
    static bool tryToChangeState(Hero* hero);

    StateSwordAirSpin(Hero* hero);
    virtual ~StateSwordAirSpin();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsEnd;
};

}
}
}
}

#endif
