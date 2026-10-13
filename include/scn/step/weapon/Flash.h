#ifndef SCN_STEP_WEAPON_FLASH_H
#define SCN_STEP_WEAPON_FLASH_H

#include "gobj/ColorAnim.h"
#include "util/PlacementNew.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

class Flash {
public:
    Flash(Weapon& weapon, mem::IAllocator& allocator, bool isValid);

    bool isValid() const;
    void updateUseGPU();
    void set(const GXColor& color, g3d::ColorAnimFlashOp op);

private:
    util::PlacementNew<gobj::ColorAnim> mColorAnim;
};

}}}  // namespace scn::step::weapon

#endif
