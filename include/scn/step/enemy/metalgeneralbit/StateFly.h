#ifndef SCN_STEP_ENEMY_METALGENERALBIT_STATEFLY_H
#define SCN_STEP_ENEMY_METALGENERALBIT_STATEFLY_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace metalgeneralbit {

class StateFly : public StateBase {
public:
    StateFly(Enemy* enemy);
    virtual ~StateFly();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::metalgeneralbit

#endif
