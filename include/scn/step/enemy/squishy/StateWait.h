#ifndef SCN_STEP_ENEMY_SQUISHY_STATEWAIT_H
#define SCN_STEP_ENEMY_SQUISHY_STATEWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace squishy {

class StateWait : public StateBase {
public:
    StateWait(Enemy* enemy);
    virtual ~StateWait();
    virtual void procAnim();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::squishy

#endif
