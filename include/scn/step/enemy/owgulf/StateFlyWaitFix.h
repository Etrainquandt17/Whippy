#ifndef SCN_STEP_ENEMY_OWGULF_STATEFLYWAITFIX_H
#define SCN_STEP_ENEMY_OWGULF_STATEFLYWAITFIX_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace owgulf {

class StateFlyWaitFix : public StateBase {
public:
    StateFlyWaitFix(Enemy* enemy);
    virtual void procMove();
};

}}}}  // namespace scn::step::enemy::owgulf

#endif
