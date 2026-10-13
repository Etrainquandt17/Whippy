#ifndef SCN_STEP_BOSS_DOUBTER_BODYCOLLCTRL_H
#define SCN_STEP_BOSS_DOUBTER_BODYCOLLCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

}
class Boss;
namespace doubter {

// TODO: the names of the states.
class BodyCollCtrl {
public:
    enum State {
        STATE_0,
        STATE_1,
        STATE_2,
        STATE_3,
        STATE_4,
    };

    BodyCollCtrl(Boss& boss);
    void onStateChange();
    void setState(State state);

private:
    void setHide();
    void setDefault();
    void setDefaultWithoutHandAttack();
    void setTornado();

    Boss& mBoss;
    State mState;
};

}}}}  // namespace scn::step::boss::doubter

#endif
