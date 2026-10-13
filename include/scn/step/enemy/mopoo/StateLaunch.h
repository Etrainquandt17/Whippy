#ifndef SCN_STEP_ENEMY_MOPOO_STATELAUNCH_H
#define SCN_STEP_ENEMY_MOPOO_STATELAUNCH_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mopoo {

// TODO: stub
class StateLaunch : public StateBase {
public:
    StateLaunch(Enemy* enemy);
};

}}}}  // namespace scn::step::enemy::mopoo

#endif
