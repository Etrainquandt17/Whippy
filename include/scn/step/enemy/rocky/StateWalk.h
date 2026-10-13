#ifndef SCN_STEP_ENEMY_ROCKY_STATEWALK_H
#define SCN_STEP_ENEMY_ROCKY_STATEWALK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace rocky {

class StateWalk : public StateBase {
public:
    StateWalk(Enemy* enemy);
    virtual ~StateWalk();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsMove;
    s32 mFrame;
    s32 mAttackFrame;
};

}}}}  // namespace scn::step::enemy::rocky

#endif
