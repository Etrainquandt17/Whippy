#ifndef SCN_STEP_HERO_STAGINGCTRL_H
#define SCN_STEP_HERO_STAGINGCTRL_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

class StagingCtrl {
public:
    void setZoom(const hel::math::Vector2& center, f32 rate);
    void setZoom(f32 rate);
    void unsetZoom();
    void setCamRot(f32 x, f32 y);
    void unsetCamRot();
};

}}}  // namespace scn::step::hero

#endif
