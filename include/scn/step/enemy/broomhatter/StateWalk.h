#ifndef SCN_STEP_ENEMY_BROOMHATTER_STATEWALK_H
#define SCN_STEP_ENEMY_BROOMHATTER_STATEWALK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace broomhatter {

class StateWalk : public StateBase {
public:
    StateWalk(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    f32 mSpeed;
    f32 mDecel;
};

}}}}  // namespace scn::step::enemy::broomhatter

#endif
