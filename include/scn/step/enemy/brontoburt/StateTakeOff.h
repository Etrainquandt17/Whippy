#ifndef SCN_STEP_ENEMY_BRONTOBURT_STATETAKEOFF_H
#define SCN_STEP_ENEMY_BRONTOBURT_STATETAKEOFF_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace brontoburt {

class StateTakeOff : public StateBase {
public:
    StateTakeOff(Enemy* enemy);
    virtual void procMove();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::brontoburt

#endif
