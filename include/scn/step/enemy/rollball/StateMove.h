#ifndef SCN_STEP_ENEMY_ROLLBALL_STATEMOVE_H
#define SCN_STEP_ENEMY_ROLLBALL_STATEMOVE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace rollball {

// TODO: stub
class StateMove : public StateBase {
public:
    StateMove(Enemy* enemy);
};

}}}}  // namespace scn::step::enemy::rollball

#endif
