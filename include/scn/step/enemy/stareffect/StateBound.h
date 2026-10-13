#ifndef SCN_STEP_ENEMY_STAREFFECT_STATEBOUND_H
#define SCN_STEP_ENEMY_STAREFFECT_STATEBOUND_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace stareffect {

// TODO: stub
class StateBound : public StateBase {
public:
    StateBound(Enemy* enemy);
};

}}}}  // namespace scn::step::enemy::stareffect

#endif
