#include "scn/step/weapon/galactarevolutionsword/StateEnd.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/galactarevolutionsword/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace galactarevolutionsword {

StateEnd::StateEnd(Weapon* weapon) : StateBase(weapon), mFrame(0.0f) {}

void StateEnd::procAnim() {
    const Param& param = obj().param().galactaRevolutionSword();
    mFrame += 1.0f;
    if (mFrame == static_cast<f32>(param._20)) {
        obj().dead();
    } else {
        f32 rate = mFrame / static_cast<f32>(param._20);
        hel::math::Vector3 scale = hel::math::Vector3::ALL_ONE * (1.0f - rate) * param._C;
        obj().model().model().nodes().at(2).localMtx().setScale(scale);
        obj().model().model().nodes().at(3).localMtx().setScale(scale);
    }
}

void StateEnd::procMove() {}

void StateEnd::procFixPos() {}

}}}}  // namespace scn::step::weapon::galactarevolutionsword
