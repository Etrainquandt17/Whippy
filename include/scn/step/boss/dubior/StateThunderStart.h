#ifndef SCN_STEP_BOSS_DUBIOR_STATETHUNDERSTART_H
#define SCN_STEP_BOSS_DUBIOR_STATETHUNDERSTART_H

#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS

#include "hel/common/MutableArray.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

class StateThunderStart : public StateBase {
public:
    StateThunderStart(Boss* boss);
    virtual ~StateThunderStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::common::MutableArray<hel::math::Vector3, 2> mTargets;
    u32 mCount;
    u32 mIndex;
    u32 _2C;
};

}}}}  // namespace scn::step::boss::dubior

#endif
