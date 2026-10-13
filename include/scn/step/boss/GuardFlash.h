#ifndef SCN_STEP_BOSS_GUARDFLASH_H
#define SCN_STEP_BOSS_GUARDFLASH_H

#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class GuardFlash {
public:
    GuardFlash();

    void update();
    void setIsValid(bool isValid);
    bool isValid() const;
    GXColor getColor() const;

private:
    GXColor mColor;
    bool mIsValid;
    u32 mCount;
};

}}}  // namespace scn::step::boss

#endif
