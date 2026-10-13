#ifndef SCN_STEP_ENEMY_BARBAR_STATEATTACK_H
#define SCN_STEP_ENEMY_BARBAR_STATEATTACK_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace barbar {

// TODO: members.
class StateAttack : public IState {
public:
    StateAttack(Enemy* enemy);
    virtual ~StateAttack();
};

}}}}  // namespace scn::step::enemy::barbar

#endif
