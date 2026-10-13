#ifndef SCN_STEP_ENEMY_SHELD_STATEJUMPSTART_H
#define SCN_STEP_ENEMY_SHELD_STATEJUMPSTART_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace sheld {

class StateJumpStart : public StateBase {
public:
    StateJumpStart(Enemy* enemy);
    virtual ~StateJumpStart();
    virtual void procAnim();
    virtual void procFixPos();

private:
    u32 mWait;
};

}}}}  // namespace scn::step::enemy::sheld

#endif
