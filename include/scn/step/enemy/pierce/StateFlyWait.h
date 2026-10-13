#ifndef SCN_STEP_ENEMY_PIERCE_STATEFLYWAIT_H
#define SCN_STEP_ENEMY_PIERCE_STATEFLYWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace pierce {

class StateFlyWait : public StateBase {
public:
    StateFlyWait(Enemy* enemy);
    virtual ~StateFlyWait();
    virtual void procAnim();
    virtual void procMove();

private:
    u32 mFrame;
    bool mIsAttack;
};

}}}}  // namespace scn::step::enemy::pierce

#endif
