#ifndef SCN_STEP_BOSS_DEADFLASH_H
#define SCN_STEP_BOSS_DEADFLASH_H

#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class DeadFlash {
public:
    DeadFlash();

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
