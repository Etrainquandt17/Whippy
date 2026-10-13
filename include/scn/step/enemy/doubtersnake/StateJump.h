#ifndef SCN_STEP_ENEMY_DOUBTERSNAKE_STATEJUMP_H
#define SCN_STEP_ENEMY_DOUBTERSNAKE_STATEJUMP_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace doubtersnake {

class StateJump : public StateBase {
public:
    StateJump(Enemy* enemy);
    virtual ~StateJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::enemy::doubtersnake

#endif
