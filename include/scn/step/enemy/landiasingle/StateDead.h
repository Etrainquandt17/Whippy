#ifndef SCN_STEP_ENEMY_LANDIASINGLE_STATEDEAD_H
#define SCN_STEP_ENEMY_LANDIASINGLE_STATEDEAD_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace landiasingle {

// TODO: stub
class StateDead : public StateBase {
public:
    StateDead(Enemy* enemy);
};

}}}}  // namespace scn::step::enemy::landiasingle

#endif
