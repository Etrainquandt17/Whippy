#ifndef SCN_STEP_BOSS_GOLIATH_STATEWALLTHROW_H
#define SCN_STEP_BOSS_GOLIATH_STATEWALLTHROW_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateWallThrow : public StateBase {
public:
    StateWallThrow(Boss* boss);
    virtual ~StateWallThrow();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void generateEnemy();
    void throwEnemy();
};

}}}}  // namespace scn::step::boss::goliath

#endif
