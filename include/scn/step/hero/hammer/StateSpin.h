#ifndef SCN_STEP_HERO_HAMMER_STATESPIN_H
#define SCN_STEP_HERO_HAMMER_STATESPIN_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

struct HammerParamSpin;
namespace hammer {

class StateSpin : public StateBase {
public:
    static bool TryToChangeStateSpin(Hero* hero);
    static bool TryToChangeStateThrow(Hero* hero);

    StateSpin(Hero* hero, bool isThrow);
    virtual ~StateSpin();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();

private:
    void turn();
    const HammerParamSpin& param() const;

    bool mIsThrow;
    bool mCanCancel;
    int mTurnWait;
};

}
}
}
}

#endif
