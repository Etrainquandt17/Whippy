#ifndef SCN_STEP_ENEMY_SODORY_STATEFLY_H
#define SCN_STEP_ENEMY_SODORY_STATEFLY_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace sodory {

class StateFly : public StateBase {
public:
    StateFly(Enemy* enemy);
    virtual ~StateFly();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    f32 _c;
};

}}}}  // namespace scn::step::enemy::sodory

#endif
