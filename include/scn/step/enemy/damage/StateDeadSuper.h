#ifndef SCN_STEP_ENEMY_DAMAGE_STATEDEADSUPER_H
#define SCN_STEP_ENEMY_DAMAGE_STATEDEADSUPER_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace damage {

class StateDeadSuper : public StateBase {
public:
    StateDeadSuper(Enemy* enemy);
    virtual ~StateDeadSuper();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
    u32 mReflectCount;
    u32 _10;
    u32 mReflectMax;
    u32 mElement;
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::damage

#endif
