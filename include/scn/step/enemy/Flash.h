#ifndef SCN_STEP_ENEMY_FLASH_H
#define SCN_STEP_ENEMY_FLASH_H

#include "g3d/ColorAnimFlashOp.h"
#include "revolution/gx/GXStruct.h"

namespace scn {
namespace step {
namespace enemy {

// TODO: members and the other functions.
class Flash {
public:
    void setEnf1F(const GXColor& color);
    void setEnf1F(const GXColor& color, g3d::ColorAnimFlashOp op);
    void setEnfAlways(const GXColor& color);
    void disableAlwaysRequest();
};

}}}  // namespace scn::step::enemy

#endif
