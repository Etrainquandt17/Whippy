#ifndef SCN_STEP_ENEMY_NRUFF_STATEWALK_H
#define SCN_STEP_ENEMY_NRUFF_STATEWALK_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace nruff {

// TODO: members.
class StateWalk : public IState {
public:
    StateWalk(Enemy* enemy);
    virtual ~StateWalk();
};

}}}}  // namespace scn::step::enemy::nruff

#endif
