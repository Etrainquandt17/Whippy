#ifndef SCN_STEP_ENEMY_MOPOO_STATEHIDE_H
#define SCN_STEP_ENEMY_MOPOO_STATEHIDE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mopoo {

class StateHide : public StateBase {
public:
    StateHide(Enemy* enemy);
    virtual void procFixPos();

private:
    int mFrame;
    int mWaitTime;
};

}}}}  // namespace scn::step::enemy::mopoo

#endif
