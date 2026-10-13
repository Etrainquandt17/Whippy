#ifndef SCN_STEP_ENEMY_LANDIASINGLE_STATEGRANDCROSSSTOP_H
#define SCN_STEP_ENEMY_LANDIASINGLE_STATEGRANDCROSSSTOP_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace landiasingle {

class StateGrandCrossStop : public StateBase {
public:
    StateGrandCrossStop(Enemy* enemy);
    virtual ~StateGrandCrossStop();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::landiasingle

#endif
