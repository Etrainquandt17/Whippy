#ifndef SCN_STEP_HERO_PARASOL_STATEPARASOLDIVE_H
#define SCN_STEP_HERO_PARASOL_STATEPARASOLDIVE_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

class StateParasolDive : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateParasolDive(Hero* hero);
    virtual ~StateParasolDive();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsDive;
    f32 mSign;
    bool mIsEffectReleased;
};

}
}
}
}

#endif
