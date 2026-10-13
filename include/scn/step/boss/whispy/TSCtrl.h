#ifndef SCN_STEP_BOSS_WHISPY_TSCTRL_H
#define SCN_STEP_BOSS_WHISPY_TSCTRL_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

}

class Boss;

namespace whispy {

class TSCtrl {
public:
    TSCtrl(Boss& boss);

    void setTrunkScale(f32 scale);
    void setBaseTrans(const hel::math::Vector3& trans);
    void setBaseScale(const hel::math::Vector3& scale);

private:
    Boss& mBoss;
};

}}}}  // namespace scn::step::boss::whispy

#endif
