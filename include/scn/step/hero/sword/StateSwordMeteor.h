#ifndef SCN_STEP_HERO_SWORD_STATESWORDMETEOR_H
#define SCN_STEP_HERO_SWORD_STATESWORDMETEOR_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordMeteor : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateSwordMeteor(Hero* hero);
    virtual ~StateSwordMeteor();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}
}
}
}

#endif
