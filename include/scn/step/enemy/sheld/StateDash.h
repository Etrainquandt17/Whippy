#ifndef SCN_STEP_ENEMY_SHELD_STATEDASH_H
#define SCN_STEP_ENEMY_SHELD_STATEDASH_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace sheld {

class StateDash : public StateBase {
public:
    StateDash(Enemy* enemy);
    virtual ~StateDash();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mAccel;
};

}}}}  // namespace scn::step::enemy::sheld

#endif
