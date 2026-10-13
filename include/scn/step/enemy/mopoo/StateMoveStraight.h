#ifndef SCN_STEP_ENEMY_MOPOO_STATEMOVESTRAIGHT_H
#define SCN_STEP_ENEMY_MOPOO_STATEMOVESTRAIGHT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mopoo {

// TODO: stub
class StateMoveStraight : public StateBase {
public:
    StateMoveStraight(Enemy* enemy);
};

}}}}  // namespace scn::step::enemy::mopoo

#endif
