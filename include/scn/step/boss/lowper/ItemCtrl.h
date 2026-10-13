#ifndef SCN_STEP_BOSS_LOWPER_ITEMCTRL_H
#define SCN_STEP_BOSS_LOWPER_ITEMCTRL_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

}
class Boss;
namespace lowper {

class ItemCtrl {
public:
    ItemCtrl(Boss& boss);
    ~ItemCtrl();

    void init();
    void update();
    bool isItemExist() const;
    void checkItemGather();
    bool isNearObj(hel::math::Vector3, hel::math::Vector3) const;
    hel::math::Vector3 getItemPos() const;
    void setupGear();
    void setupSRTTarget();

private:
    // TODO: members.
    u32 _0[0xA0 / 4];
};

}}}}  // namespace scn::step::boss::lowper

#endif
