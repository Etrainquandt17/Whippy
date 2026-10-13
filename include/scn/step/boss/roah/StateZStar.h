#ifndef SCN_STEP_BOSS_ROAH_STATEZSTAR_H
#define SCN_STEP_BOSS_ROAH_STATEZSTAR_H

#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS

#include "hel/common/MutableArray.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateZStar : public StateBase {
public:
    struct Config {
        u32 _0;
        f32 _4;
        f32 _8;
        u32 _C;
        bool _10;
    };

    StateZStar(Boss* boss, Config config);
    virtual ~StateZStar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqStar();

    u32 mCount;
    u32 mIndex;
    hel::common::MutableArray<hel::math::Vector3, 6> mPoints;
    hel::math::Vector3 mBasePos;
    Config mConfig;
};

}}}}  // namespace scn::step::boss::roah

#endif
