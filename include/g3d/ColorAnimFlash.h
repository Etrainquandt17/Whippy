#ifndef G3D_COLORANIMFLASH_H
#define G3D_COLORANIMFLASH_H

#include "g3d/ColorAnimFlashOp.h"
#include "revolution/gx/GXStruct.h"

namespace g3d {

class ColorAnimFlash {
public:
    ColorAnimFlash();

    void setColor(const GXColor& color);
    void setOperation(ColorAnimFlashOp op);

private:
    GXColor mColor;
    ColorAnimFlashOp mOperation;
};

}

#endif
