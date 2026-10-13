#ifndef SCN_STEP_BOSS_BRAINCTRL_H
#define SCN_STEP_BOSS_BRAINCTRL_H

#include "mint/Runner.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

class BrainCtrl {
public:
    BrainCtrl(Boss& boss);

    void update();
    void set(const char* name);
    void toValid();
    void toInvalid();
    bool isValid() const;

private:
    void onExecPre();
    void onExecPost();

    Boss& mBoss;
    mint::Runner mRunner;
    bool mIsValid;
    bool mIsSet;
};

}
}
}

#endif
