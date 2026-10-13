#ifndef SCN_STEP_ENEMY_LANZER_STATEWALKAROUND_H
#define SCN_STEP_ENEMY_LANZER_STATEWALKAROUND_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace lanzer {

// TODO: members.
class StateWalkAround : public IState {
public:
    StateWalkAround(Enemy* enemy);
    virtual ~StateWalkAround();
};

}}}}  // namespace scn::step::enemy::lanzer

#endif
