#ifndef SCN_STEP_HERO_PARASOL_STATEPARASOLPARACHUTEFALL_H
#define SCN_STEP_HERO_PARASOL_STATEPARASOLPARACHUTEFALL_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

class StateParasolParachuteFall : public StateBase {
public:
    StateParasolParachuteFall(Hero* hero);
    virtual ~StateParasolParachuteFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mFallFrame;
};

}
}
}
}

#endif
