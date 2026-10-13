#ifndef SCN_STEP_BOSS_HRD3_STATEFLYINGBODYPRESSFALL_H
#define SCN_STEP_BOSS_HRD3_STATEFLYINGBODYPRESSFALL_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StateFlyingBodyPressFall : public StateBase {
public:
    StateFlyingBodyPressFall(Boss* boss);
    virtual ~StateFlyingBodyPressFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector3 mStartPos;
};

}}}}  // namespace scn::step::boss::hrd3

#endif
