#ifndef SCN_STEP_GIMMICK_WARPSTAR_MANAGER_H
#define SCN_STEP_GIMMICK_WARPSTAR_MANAGER_H

#include "hel/math/Matrix34.h"

namespace scn {
namespace step {
namespace gimmick {
namespace warpstar {

class Manager {
public:
    bool isExist() const;
    void setVisibility(bool isVisible);
    bool isVisible();
    void startAppearAnim();
    bool isDemoStarted() const;
    hel::math::Matrix34 kirbyRideWorldMtx();
};

}}}}  // namespace scn::step::gimmick::warpstar

#endif
