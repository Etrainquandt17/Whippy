#include "scn/step/weapon/Flash.h"

#include "scn/step/chara/Model.h"
#include "scn/step/weapon/Weapon.h"

using g3d::ColorAnimFlash;
using g3d::ColorAnimFlashOp;
using g3d::ColorAnimFlashOp_0;

namespace scn {
namespace step {
namespace weapon {

// TODO: the zero of the initialisers and the model trade r30 and r31, as in boss::Flash; everything else matches.
Flash::Flash(Weapon& weapon, mem::IAllocator& allocator, bool isValid) : mColorAnim() {
    if (isValid) {
        // TODO: gobj::GearModel is a gobj::IG3DModel; its header does not say so yet.
        gobj::IG3DModel& model = *reinterpret_cast<gobj::IG3DModel*>(&weapon.model().model());
        mColorAnim.construct<gobj::ColorAnimDesc, mem::IAllocator&, gobj::IG3DModel&>(gobj::ColorAnimDesc(), allocator, model);
        ColorAnimFlash flash;
        flash.setColor((GXColor){ 0, 0, 0, 0 });
        flash.setOperation(ColorAnimFlashOp_0);
        mColorAnim->setFlash(flash);
    }
}

bool Flash::isValid() const {
    return mColorAnim.isConstruct();
}

void Flash::updateUseGPU() {
    if (mColorAnim.isConstruct()) {
        mColorAnim->updateUseGPU();
    }
}

void Flash::set(const GXColor& color, ColorAnimFlashOp op) {
    if (mColorAnim.isConstruct()) {
        ColorAnimFlash flash = mColorAnim->flash();
        flash.setColor(color);
        flash.setOperation(op);
        mColorAnim->setFlash(flash);
    }
}

}}}  // namespace scn::step::weapon
