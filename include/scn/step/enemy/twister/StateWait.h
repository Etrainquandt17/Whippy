#ifndef SCN_STEP_ENEMY_TWISTER_STATEWAIT_H
#define SCN_STEP_ENEMY_TWISTER_STATEWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace twister {

class StateWait : public StateBase {
public:
    StateWait(Enemy* enemy);
    virtual ~StateWait();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::twister

#endif
