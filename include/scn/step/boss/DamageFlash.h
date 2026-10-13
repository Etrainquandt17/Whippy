#ifndef SCN_STEP_BOSS_DAMAGEFLASH_H
#define SCN_STEP_BOSS_DAMAGEFLASH_H

#include "revolution/gx/GXStruct.h"
#include "scn/step/ocoll/Element.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class DamageFlash {
public:
    DamageFlash();

    void update();
    void set(ocoll::Element element, u32 frame);
    void cancel();
    bool isValid() const;
    GXColor getColor() const;

private:
    GXColor mColor;
    u32 mFrame;
    u32 mCount;
    u32 mCombo;
};

}}}  // namespace scn::step::boss

#endif
