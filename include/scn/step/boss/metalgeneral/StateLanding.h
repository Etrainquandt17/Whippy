#ifndef SCN_STEP_BOSS_METALGENERAL_STATELANDING_H
#define SCN_STEP_BOSS_METALGENERAL_STATELANDING_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateLanding : public StateBase {
public:
    StateLanding(Boss* boss);
    virtual ~StateLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
