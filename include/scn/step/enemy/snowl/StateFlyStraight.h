#ifndef SCN_STEP_ENEMY_SNOWL_STATEFLYSTRAIGHT_H
#define SCN_STEP_ENEMY_SNOWL_STATEFLYSTRAIGHT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace snowl {

// TODO: stub
class StateFlyStraight : public StateBase {
public:
    StateFlyStraight(Enemy* enemy);
};

}}}}  // namespace scn::step::enemy::snowl

#endif
