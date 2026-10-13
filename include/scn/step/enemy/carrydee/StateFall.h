#ifndef SCN_STEP_ENEMY_CARRYDEE_STATEFALL_H
#define SCN_STEP_ENEMY_CARRYDEE_STATEFALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace carrydee {

// TODO: stub
class StateFall : public StateBase {
public:
    StateFall(Enemy* enemy);
};

}}}}  // namespace scn::step::enemy::carrydee

#endif
