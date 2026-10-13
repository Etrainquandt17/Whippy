#ifndef SCN_STEP_BOSS_LOWPER_STATEMOVETOOTHERSIDE_H
#define SCN_STEP_BOSS_LOWPER_STATEMOVETOOTHERSIDE_H

#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS

#include "hel/common/MutableArray.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateMoveToOtherSide : public StateBase {
public:
    StateMoveToOtherSide(Boss* boss);
    virtual ~StateMoveToOtherSide();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::common::MutableArray<hel::math::Vector3, 5> mPositions;
    u32 mCount;
    u32 mIndex;
};

}}}}  // namespace scn::step::boss::lowper

#endif
