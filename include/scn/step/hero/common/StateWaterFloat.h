#ifndef SCN_STEP_HERO_COMMON_STATEWATERFLOAT_H
#define SCN_STEP_HERO_COMMON_STATEWATERFLOAT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateWaterFloat : public StateBase {
public:
    StateWaterFloat(Hero* hero);
    virtual ~StateWaterFloat();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqJumpEffect();
    void updateNinjaViewOffset();

    bool mIsMove;
    u32 mFrame;
    bool mIsNinja;
};

}
}
}
}

#endif
