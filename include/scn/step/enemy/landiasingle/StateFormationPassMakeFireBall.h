#ifndef SCN_STEP_ENEMY_LANDIASINGLE_STATEFORMATIONPASSMAKEFIREBALL_H
#define SCN_STEP_ENEMY_LANDIASINGLE_STATEFORMATIONPASSMAKEFIREBALL_H

#include "scn/step/enemy/StateBase.h"
#include "scn/step/enemy/landiasingle/StateFormationPass.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace landiasingle {

class StateFormationPassMakeFireBall : public StateBase {
public:
    StateFormationPassMakeFireBall(Enemy* enemy, StateFormationPass::Config config);
    virtual ~StateFormationPassMakeFireBall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    StateFormationPass::Config mConfig;
};

}}}}  // namespace scn::step::enemy::landiasingle

#endif
