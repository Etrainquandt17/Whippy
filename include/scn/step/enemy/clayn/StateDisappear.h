#ifndef SCN_STEP_ENEMY_CLAYN_STATEDISAPPEAR_H
#define SCN_STEP_ENEMY_CLAYN_STATEDISAPPEAR_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace clayn {

class StateDisappear : public StateBase {
public:
    StateDisappear(Enemy* enemy);
    virtual ~StateDisappear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::clayn

#endif
