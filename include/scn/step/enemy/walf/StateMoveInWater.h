#ifndef SCN_STEP_ENEMY_WALF_STATEMOVEINWATER_H
#define SCN_STEP_ENEMY_WALF_STATEMOVEINWATER_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace walf {

class StateMoveInWater : public StateBase {
public:
    StateMoveInWater(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void setBubbleEffect();
    
    util::FrameCounter mJumpCounter;
    util::FrameCounter mMoveCounter;
    bool mIsFloating;
};

}}}}  // namespace scn::step::enemy::walf

#endif
