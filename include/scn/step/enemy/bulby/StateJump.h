#ifndef SCN_STEP_ENEMY_BULBY_STATEJUMP_H
#define SCN_STEP_ENEMY_BULBY_STATEJUMP_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace bulby {

class StateJump : public StateBase {
public:
    StateJump(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
};

}}}}  // namespace scn::step::enemy::bulby

#endif
