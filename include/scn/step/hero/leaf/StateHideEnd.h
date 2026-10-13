#ifndef SCN_STEP_HERO_LEAF_STATEHIDEEND_H
#define SCN_STEP_HERO_LEAF_STATEHIDEEND_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

class StateHideEnd : public StateBase {
public:
    StateHideEnd(Hero* hero);
    virtual ~StateHideEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsUnsetXlu;
};

}
}
}
}

#endif
