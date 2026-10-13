#include "scn/step/weapon/hrd3eyelaser/StateEnd.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace hrd3eyelaser {

StateEnd::StateEnd(Weapon* weapon, u32 frame)
    : StateBase(weapon)
    , mFrame(0.0f)
    , mTotalFrame(static_cast<f32>(frame)) {}

void StateEnd::procAnim() {
    mFrame += 1.0f;
    if (mFrame == mTotalFrame) {
        obj().dead();
    } else {
        f32 rate = 1.0f - mFrame / mTotalFrame;
        hel::math::Vector3 scale(rate, rate, 1.0f);
        obj().model().model().nodes().at(1).localMtx().setScale(scale);
        obj().model().model().nodes().at(2).localMtx().setScale(scale);
    }
}

void StateEnd::procMove() {}

void StateEnd::procFixPos() {}

}}}}  // namespace scn::step::weapon::hrd3eyelaser
