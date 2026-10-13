#ifndef SCN_STEP_BOSS_METALGENERAL_DAMAGEINFOCTRL_H
#define SCN_STEP_BOSS_METALGENERAL_DAMAGEINFOCTRL_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

}
class Boss;
namespace metalgeneral {

class DamageInfoCtrl {
public:
    DamageInfoCtrl(Boss& boss);

    void set(u32 damage);
    void request(u32 digit, u32 place, hel::math::Vector3 pos, f32 scale);
#ifdef VERSION_SUKK01
    void requestAddSpaceDigit4(u32 digit, hel::math::Vector3 pos, f32 scale);
    void requestAddCommaDigit4(u32 digit, hel::math::Vector3 pos, f32 scale);
#endif

private:
    Boss& mBoss;
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
