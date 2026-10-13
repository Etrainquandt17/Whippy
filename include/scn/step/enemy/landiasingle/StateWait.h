#ifndef SCN_STEP_ENEMY_LANDIASINGLE_STATEWAIT_H
#define SCN_STEP_ENEMY_LANDIASINGLE_STATEWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace landiasingle {

// TODO: stub
class StateWait : public StateBase {
public:
    StateWait(Enemy* enemy, bool isFirst);
};

}}}}  // namespace scn::step::enemy::landiasingle

#endif
