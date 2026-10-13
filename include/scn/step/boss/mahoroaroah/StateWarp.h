#ifndef SCN_STEP_BOSS_MAHOROAROAH_STATEWARP_H
#define SCN_STEP_BOSS_MAHOROAROAH_STATEWARP_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroaroah {

class StateWarp : public StateBase {
public:
    enum WarpKind {
        WARP_KIND_0,
        WARP_KIND_1,
    };

    StateWarp(Boss* boss, WarpKind kind);
    virtual ~StateWarp();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    WarpKind mKind;
};

}
}
}
}

#endif
