#ifndef SCN_STEP_ENEMY_METALGENERALBIT_STATEMOVE_H
#define SCN_STEP_ENEMY_METALGENERALBIT_STATEMOVE_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace metalgeneralbit {

// TODO: members.
class StateMove : public IState {
public:
    StateMove(Enemy* enemy);
    virtual ~StateMove();
};

}}}}  // namespace scn::step::enemy::metalgeneralbit

#endif
