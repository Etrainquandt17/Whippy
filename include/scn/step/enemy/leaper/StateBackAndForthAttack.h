#ifndef SCN_STEP_ENEMY_LEAPER_STATEBACKANDFORTHATTACK_H
#define SCN_STEP_ENEMY_LEAPER_STATEBACKANDFORTHATTACK_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace leaper {

// TODO: members.
class StateBackAndForthAttack : public IState {
public:
    StateBackAndForthAttack(Enemy* enemy);
    virtual ~StateBackAndForthAttack();
};

}}}}  // namespace scn::step::enemy::leaper

#endif
