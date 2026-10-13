#ifndef SCN_STEP_ENEMY_GRANDLOWPERBULLET_STATEHOMING_H
#define SCN_STEP_ENEMY_GRANDLOWPERBULLET_STATEHOMING_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace grandlowperbullet {

class StateHoming : public StateBase {
public:
    StateHoming(Enemy* enemy);
    virtual ~StateHoming();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mXluFrame;
};

}}}}  // namespace scn::step::enemy::grandlowperbullet

#endif
