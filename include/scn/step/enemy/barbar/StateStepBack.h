#ifndef SCN_STEP_ENEMY_BARBAR_STATESTEPBACK_H
#define SCN_STEP_ENEMY_BARBAR_STATESTEPBACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace barbar {

class StateStepBack : public StateBase {
public:
    StateStepBack(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();

private:
    bool mIsHidden;
};

}}}}  // namespace scn::step::enemy::barbar

#endif
