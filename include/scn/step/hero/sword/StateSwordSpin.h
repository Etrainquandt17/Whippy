#ifndef SCN_STEP_HERO_SWORD_STATESWORDSPIN_H
#define SCN_STEP_HERO_SWORD_STATESWORDSPIN_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordSpin : public StateBase {
public:
    StateSwordSpin(Hero* hero);
    virtual ~StateSwordSpin();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsEnd;
};

}
}
}
}

#endif
