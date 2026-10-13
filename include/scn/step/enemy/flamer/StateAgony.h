#ifndef SCN_STEP_ENEMY_FLAMER_STATEAGONY_H
#define SCN_STEP_ENEMY_FLAMER_STATEAGONY_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace flamer {

// TODO: members.
class StateAgony : public IState {
public:
    StateAgony(Enemy* enemy);
    virtual ~StateAgony();
};

}}}}  // namespace scn::step::enemy::flamer

#endif
