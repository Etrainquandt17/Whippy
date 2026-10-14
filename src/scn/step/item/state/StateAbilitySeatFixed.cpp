#include "scn/step/item/state/StateAbilitySeatFixed.h"

#include "g3d/ModelAccessor.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "hel/math/Matrix34.h"
#include "scn/step/chara/Model.h"
#include "scn/step/item/Item.h"
#include "scn/step/item/RotAnim.h"

using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace item {
namespace state {

StateAbilitySeatFixed::StateAbilitySeatFixed(Item* item, f32 rot)
    : StateBase(item)
    , mRot(rot) {
    obj().rotAnim().setIsEnable(false);
}

StateAbilitySeatFixed::~StateAbilitySeatFixed() {
    obj().rotAnim().setIsEnable(true);
}

void StateAbilitySeatFixed::procAnim() {
    if (obj().isRequireRotAnim()) {
        mRot -= 4.0f;
        if (mRot < 0.0f) {
            mRot += 360.0f;
        }
        Matrix34 mtx = Matrix34::CreateRotAxisDeg(Vector3::BASIS_Y, mRot);
        obj().model().model().g3dModel().nodeByName("FootL").localMtx().setRTMtx(mtx);
    }
}

}}}}  // namespace scn::step::item::state
