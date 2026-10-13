#ifndef SCN_STEP_ENEMY_BROOMHATTER_STATEWALKAROUND_H
#define SCN_STEP_ENEMY_BROOMHATTER_STATEWALKAROUND_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace broomhatter {

class StateWalkAround : public StateBase {
public:
    StateWalkAround(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

    void initBrush();

private:
    u32 mTurnCount;
    u32 mFrame;
    f32 mSpeed;
    f32 mDecel;
};

}}}}  // namespace scn::step::enemy::broomhatter

#endif
