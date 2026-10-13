#ifndef SCN_STEP_ENEMY_BABUT_STATEDOUBTERAPPEAR_H
#define SCN_STEP_ENEMY_BABUT_STATEDOUBTERAPPEAR_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace babut {

class StateDoubterAppear : public StateBase {
public:
    StateDoubterAppear(Enemy* enemy);
    virtual ~StateDoubterAppear();
    virtual void procAnim();
    virtual void procMove();
};

}}}}  // namespace scn::step::enemy::babut

#endif
