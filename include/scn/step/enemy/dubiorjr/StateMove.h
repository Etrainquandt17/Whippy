#ifndef SCN_STEP_ENEMY_DUBIORJR_STATEMOVE_H
#define SCN_STEP_ENEMY_DUBIORJR_STATEMOVE_H

#include "scn/step/enemy/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace dubiorjr {

// TODO: members.
class StateMove : public IState {
public:
    StateMove(Enemy* enemy, f32, f32);
    virtual ~StateMove();
};

}}}}  // namespace scn::step::enemy::dubiorjr

#endif
