#ifndef SCN_STEP_BOSS_CUSTOMFLASH_H
#define SCN_STEP_BOSS_CUSTOMFLASH_H

#include "g3d/ColorAnimFlashOp.h"
#include "revolution/gx/GXStruct.h"

namespace scn {
namespace step {
namespace boss {

class CustomFlash {
public:
    CustomFlash();

    void update();
    void setIsValid(bool isValid);
    bool isValid() const;
    void setColor(const GXColor& color);
    void setOperation(g3d::ColorAnimFlashOp op);
    GXColor getColor() const;
    g3d::ColorAnimFlashOp getOperation() const;

private:
    GXColor mColor;
    g3d::ColorAnimFlashOp mOperation;
    bool mIsValid;
};

}
}
}

#endif
