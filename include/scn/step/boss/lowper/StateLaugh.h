#ifndef SCN_STEP_BOSS_LOWPER_STATELAUGH_H
#define SCN_STEP_BOSS_LOWPER_STATELAUGH_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateLaugh : public StateBase {
public:
    StateLaugh(Boss* boss);
    virtual ~StateLaugh();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
