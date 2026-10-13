#ifndef SCN_STEP_ENEMY_DUBIORSPARK_STATESHOT_H
#define SCN_STEP_ENEMY_DUBIORSPARK_STATESHOT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace dubiorspark {

class StateShot : public StateBase {
public:
    StateShot(Enemy* enemy);
    virtual ~StateShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::dubiorspark

#endif
