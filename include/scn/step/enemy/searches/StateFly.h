#ifndef SCN_STEP_ENEMY_SEARCHES_STATEFLY_H
#define SCN_STEP_ENEMY_SEARCHES_STATEFLY_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace searches {

class StateFly : public StateBase {
public:
    StateFly(Enemy* enemy);
    virtual void procAnim();
};

}}}}  // namespace scn::step::enemy::searches

#endif
