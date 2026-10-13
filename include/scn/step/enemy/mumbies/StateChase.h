#ifndef SCN_STEP_ENEMY_MUMBIES_STATECHASE_H
#define SCN_STEP_ENEMY_MUMBIES_STATECHASE_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mumbies {

// TODO: members.
class StateChase : public IState {
public:
    StateChase(Enemy* enemy);
    virtual ~StateChase();
};

}}}}  // namespace scn::step::enemy::mumbies

#endif
