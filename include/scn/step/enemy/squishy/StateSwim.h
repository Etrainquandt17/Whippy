#ifndef SCN_STEP_ENEMY_SQUISHY_STATESWIM_H
#define SCN_STEP_ENEMY_SQUISHY_STATESWIM_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace squishy {

class StateSwim : public StateBase {
public:
    StateSwim(Enemy* enemy);
    virtual ~StateSwim();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
    bool mIsLooped;
};

}}}}  // namespace scn::step::enemy::squishy

#endif
