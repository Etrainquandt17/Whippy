#ifndef SCN_STEP_ENEMY_NRUFF_STATEFALL_H
#define SCN_STEP_ENEMY_NRUFF_STATEFALL_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace nruff {

// TODO: members. A stand-in until the unit is written: the base and the destructor are not checked.
class StateFall : public IState {
public:
    StateFall(Enemy* enemy);
    virtual ~StateFall();
};

}}}}  // namespace scn::step::enemy::nruff

#endif
