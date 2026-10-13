#ifndef SCN_STEP_ENEMY_PIERCE_STATEFLYPURSUIT_H
#define SCN_STEP_ENEMY_PIERCE_STATEFLYPURSUIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace pierce {

// TODO: stub
class StateFlyPursuit : public StateBase {
public:
    StateFlyPursuit(Enemy* enemy);
};

}}}}  // namespace scn::step::enemy::pierce

#endif
