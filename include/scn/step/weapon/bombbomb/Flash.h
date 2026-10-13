#ifndef SCN_STEP_WEAPON_BOMBBOMB_FLASH_H
#define SCN_STEP_WEAPON_BOMBBOMB_FLASH_H

#include "revolution/gx/GXStruct.h"
#include "scn/step/weapon/Weapon.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace bombbomb {

class Flash {
public:
    enum FlashKind {
        FLASH_KIND_NORMAL,
        FLASH_KIND_FAST,
    };

    Flash(Weapon& weapon);

    void update();
    void setFast();
    void updateNormal();
    void updateFast();
    ::GXColor GXColor();

private:
    Weapon& mObj;
    FlashKind mKind;
    f32 mAngle;
    u32 mWait;
};

}}}}  // namespace scn::step::weapon::bombbomb

#endif
