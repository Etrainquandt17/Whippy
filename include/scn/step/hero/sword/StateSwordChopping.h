#ifndef SCN_STEP_HERO_SWORD_STATESWORDCHOPPING_H
#define SCN_STEP_HERO_SWORD_STATESWORDCHOPPING_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordChopping : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);
    static bool RetryToChangeState(Hero* hero);

    StateSwordChopping(Hero* hero, bool isRetry);
    virtual ~StateSwordChopping();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();

private:
    u32 mFrame;
    bool mIsRetry;
};

}
}
}
}

#endif
