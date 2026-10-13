#ifndef SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTGENERATE_H
#define SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTGENERATE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StatePatriotGenerate : public StateBase {
public:
    struct Config {
        u32 _0;
        bool _4;
        int _8;
    };

    StatePatriotGenerate(Boss* boss, Config config);
    virtual ~StatePatriotGenerate();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    Config mConfig;
};

}
}
}
}

#endif
