#ifndef SCN_STEP_ENEMY_COMMON_STATESHOOTINGFLY_H
#define SCN_STEP_ENEMY_COMMON_STATESHOOTINGFLY_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateShootingFly : public StateBase {
public:
    StateShootingFly(Enemy* enemy);
    StateShootingFly(Enemy* enemy, f32 _8);
    virtual ~StateShootingFly();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void init();

    f32 _8;
};

}}}}  // namespace scn::step::enemy::common

#endif
