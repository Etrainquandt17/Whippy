#ifndef SCN_STEP_ENEMY_GOLIATHSNOWBALL_STATEFOLLOW_H
#define SCN_STEP_ENEMY_GOLIATHSNOWBALL_STATEFOLLOW_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace goliathsnowball {

// TODO: stub
class StateFollow : public StateBase {
public:
    StateFollow(Enemy* enemy);
};

}}}}  // namespace scn::step::enemy::goliathsnowball

#endif
