#ifndef SCN_STEP_BOSS_STATECALLBACK_H
#define SCN_STEP_BOSS_STATECALLBACK_H

#include "types.h"
#include "util/IStateCallback.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

class StateCallback : public util::IStateCallback {
public:
    StateCallback(Boss& boss);

    virtual void onStateChanged(const util::IStateChanger& changer);

    void setCanClearAttack(bool canClearAttack);

private:
    Boss& mBoss;
    bool mCanClearAttack;
};

}
}
}

#endif
