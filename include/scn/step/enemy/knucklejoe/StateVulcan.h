#ifndef SCN_STEP_ENEMY_KNUCKLEJOE_STATEVULCAN_H
#define SCN_STEP_ENEMY_KNUCKLEJOE_STATEVULCAN_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace knucklejoe {

class StateVulcan : public StateBase {
public:
    StateVulcan(Enemy* enemy);
    virtual ~StateVulcan();
    virtual void procAnim();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::knucklejoe

#endif
