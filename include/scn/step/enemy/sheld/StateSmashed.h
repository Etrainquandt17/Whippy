#ifndef SCN_STEP_ENEMY_SHELD_STATESMASHED_H
#define SCN_STEP_ENEMY_SHELD_STATESMASHED_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace sheld {

class StateSmashed : public StateBase {
public:
    StateSmashed(Enemy* enemy);
    virtual ~StateSmashed();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    f32 mRot;
    bool mIsLanded;
};

}}}}  // namespace scn::step::enemy::sheld

#endif
