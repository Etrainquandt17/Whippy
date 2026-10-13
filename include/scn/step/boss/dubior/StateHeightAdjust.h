#ifndef SCN_STEP_BOSS_DUBIOR_STATEHEIGHTADJUST_H
#define SCN_STEP_BOSS_DUBIOR_STATEHEIGHTADJUST_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

class StateHeightAdjust : public StateBase {
public:
    StateHeightAdjust(Boss* boss);
    virtual ~StateHeightAdjust();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector2 mMove;
    u32 mCount;
};

}}}}  // namespace scn::step::boss::dubior

#endif
