#ifndef SCN_STEP_ENEMY_BULBY_STATEHIDE_H
#define SCN_STEP_ENEMY_BULBY_STATEHIDE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace bulby {

class StateHide : public StateBase {
public:
    StateHide(Enemy* enemy);
    virtual void procAnim();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::bulby

#endif
