#ifndef SCN_STEP_WEAPON_BOMBBOMB_EXPAND_H
#define SCN_STEP_WEAPON_BOMBBOMB_EXPAND_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace bombbomb {

class Expand {
public:
    enum ExpandKind {
        EXPAND_KIND_NORMAL,
        EXPAND_KIND_FAST,
    };

    Expand();

    void update();
    hel::math::Vector3 scale();
    void setNormal();
    void setFast();
    void init(ExpandKind kind);
    void updateNormal();
    void updateFast();

private:
    ExpandKind mKind;
    f32 mAngle;
    u32 mWait;
    bool mIsValid;
};

}}}}  // namespace scn::step::weapon::bombbomb

#endif
