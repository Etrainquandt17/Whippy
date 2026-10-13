#ifndef SCN_STEP_BOSS_LANDIA_STATEWINDCUTTER_H
#define SCN_STEP_BOSS_LANDIA_STATEWINDCUTTER_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

class StateWindCutter : public StateBase {
public:
    struct Config {
        int _0;
    };

    StateWindCutter(Boss* boss, Config config);
    virtual ~StateWindCutter();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqWindCutter(bool isBig);

    Config mConfig;
};

}
}
}
}

#endif
