#include "scn/step/weapon/needleshot/StateStickObj.h"

#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/needleshot/Param.h"

using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace needleshot {

StateStickObj::StateStickObj(Weapon* weapon) : StateBase(weapon), mAlgorithm(*weapon), mFrame(0) {
    f32 rot = obj().model().rotCtrl().getRotV();
    f32 length = obj().param().needleShot()._10;
    mAlgorithm.setOffset(
        Vector3(
        length * Math::CosDegF(rot), length * Math::SinDegF(rot), obj().param().needleShot()._14
        )
    );
}

StateStickObj::~StateStickObj() {}

void StateStickObj::procAnim() {
    mFrame++;
    if (mFrame >= obj().param().needleShot()._18) {
        obj().dead();
    }
}

void StateStickObj::procMove() {
    mAlgorithm.procMove();
}

}}}}  // namespace scn::step::weapon::needleshot
