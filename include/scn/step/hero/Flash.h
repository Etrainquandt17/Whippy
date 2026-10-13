#ifndef SCN_STEP_HERO_FLASH_H
#define SCN_STEP_HERO_FLASH_H

#include "g3d/ColorAnimFlashOp.h"
#include "revolution/gx/GXStruct.h"

namespace scn {
namespace step {
namespace hero {

// TODO: members.
class Flash {
public:
    void setValid(bool isValid);
    void setCustomColor(const GXColor& color, const g3d::ColorAnimFlashOp& op);
    void unsetCustomColor();
};

}}}  // namespace scn::step::hero

#endif
