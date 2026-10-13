#ifndef SCN_STEP_ENEMY_GEMRA_STATEFLY_H
#define SCN_STEP_ENEMY_GEMRA_STATEFLY_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace gemra {

class StateFly : public StateBase {
public:
    StateFly(Enemy* enemy);
    virtual ~StateFly();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mWaitFrame;
};

}}}}  // namespace scn::step::enemy::gemra

#endif
