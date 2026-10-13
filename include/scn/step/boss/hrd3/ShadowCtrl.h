#ifndef SCN_STEP_BOSS_HRD3_SHADOWCTRL_H
#define SCN_STEP_BOSS_HRD3_SHADOWCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

}
class Boss;
namespace hrd3 {

// TODO: members.
class ShadowCtrl {
public:
    ShadowCtrl(Boss& boss);
    ~ShadowCtrl();

    void update();
    void updateUseGPU();
    void setVisibility(bool isVisible);
    void setVisibilityHand(bool isVisible);
};

}}}}  // namespace scn::step::boss::hrd3

#endif
